#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "path.h"
#include "sfile.h"
#include "utils.h"
#include "midi.h"

/*
TODO: The format strings were fucked up in the original binary, and didn't even print properly when an error did occur. Replace them with new, readable error messages.
 */

#if defined(__linux__)

#include <linux/limits.h>

#elif defined(_WIN32)
#include <windows.h>
#define PATH_MAX MAX_PATH
#endif

void print_program_header() {
    printf("\n%s", "/------------------------------------------------------/\n"
            "| MID2AGB 1.05                    Standard MIDI -> AGB |\n"
            "|      Copyright (c) 1999-2001, NINTENDO Co.,Ltd.      |\n"
            "/------------------------------------------------------/\n"
    );

}

void print_program_usage() {
    printf("\n%s", "Usage: MID2AGB input_file [output_file] [options]\n\n"
            "    input_file  Filename(.MID) of Standard MIDI file.\n"
            "   output_file  Filename(.s) for AGB file.(default:input_file)\n\n"
            "options  -L???  Label for assembler.(default:output_file)\n"
            "         -V???  master Volume.(default:127)\n"
            "         -G???  voiceGroup number.(default:0)\n"
            "         -P???  Priority.(default:0)\n"
            "         -R???  Reverb.(default:off)\n"
            "            -X  48 clock/beet.(default:24 c/b)\n"
            "            -E  Exact gate-time.\n"
            "            -N  No compression.\n"
    );
    exit(1);
}

void clean_up() {
    if (!fclose(output_file_fp))
        remove(output_file_name);
}

char *parse_option_parameter(int *argc, const char **argv) {
    char *parameter = NULL;

    /* Option string must be exactly 2 characters */
    if (strlen(argv[*argc]) == 2) {
        /* Get the argument directly after the current argument */
        *argc = *argc + 1;
        parameter = (char *) argv[*argc];

        /* No value, so the passed arguments are invalid */
        if (!parameter)
            print_program_usage();

        return parameter;
    }
    return NULL;
}

char *malloc_path_str(const char *str) {
    void *buffer;

    buffer = malloc(PATH_MAX);
    if (buffer)
        return strcpy((char *) buffer, str);

    return NULL;
}

int main(int argc, const char **argv) {
    const char *arg;
    int i;

    print_program_header();


    for (i = 1; argc > i; ++i) {
        arg = argv[i];

        if (*arg == '-' || *arg == '/') {
            /* Parse command line flags */
            switch (tolower(arg[1])) {
                default:
                    print_program_usage();
                    return 1;
                case 'b':
                    /* Unknown, undocumented option */
                    option_b = true;
                    break;
                case 'e':
                    /* Exact gate number */
                    option_exact_gate_time = true;
                    break;
                case 'g':
                    /* Voice group selection */
                    sscanf(parse_option_parameter(&i, argv), "%d", &option_voicegroup);
                    break;
                case 'l':
                    /* Assembler label */
                    assembler_label = parse_option_parameter(&i, argv);
                    break;
                case 'n':
                    /* Disabled compression */
                    option_compression_enabled = false;
                    break;
                case 'p':
                    /* Priority */
                    sscanf(parse_option_parameter(&i, argv), "%d", &option_priority);
                    break;
                case 'r':
                    /* Reverb */
                    sscanf(parse_option_parameter(&i, argv), "%d", &option_reverb);
                    break;
                case 'v':
                    /* Volume */
                    sscanf(parse_option_parameter(&i, argv), "%d", &option_volume);
                    break;
                case 'x':
                    /* 48 clock/beat or 24 clock per beat */
                    option_clock_per_beat = 2;
                    break;
            }
        }
        else                                        // Check if input file
        {
            /* Parse file names intuitively */

            /* If the input file is set, we must set the output file */
            if (input_file_name) {

                /* If both input and output are set, too many options were provided */
                if (output_file_name)
                    print_program_usage();

                /* Set the output name */
                output_file_name = (char *) argv[i];
            }
            else {
                /* First non-flag option is always assumed to be the input */
                input_file_name = (char *) argv[i];
            }
        }
    }

    /* No paths were provided */
    if (!input_file_name)
        print_program_usage();

    /* Allocate input path string for path modification */
    input_file_name = malloc_path_str(input_file_name);
    if (!input_file_name)
        print_error("%s", "fn1");

    /* Add the extension if none was provided */
    if (!check_extension(input_file_name, NULL))
        resolve_path_and_extension(input_file_name, "mid");

    /* Create the correct file if no output path was provided */
    if (!output_file_name) {
        output_file_name = malloc_path_str(input_file_name);
        if (!output_file_name)
            print_error("%s", "fn2");
        resolve_path_and_extension(output_file_name, "s");
    }

    /* Create label if none was povided */
    if (!assembler_label) {
        assembler_label = strip_extension(output_file_name);
        if (!assembler_label)
            print_error("%s", "lbl");
    }

    /* Allocate the events buffers */
    control_events_buffer = (Event *) malloc(sizeof(Event) * 10000);
    if (!control_events_buffer)
        print_error("%s", "lbuf1");

    merged_events_buffer = (Event *) malloc(sizeof(Event) * 10000);
    if (!merged_events_buffer)
        print_error("%s", "lbuf2");

    meta_events_buffer = (Event *) malloc(sizeof(Event) * 1000);
    if (!meta_events_buffer)
        print_error("%s", "sbuf1");

    buffer_512 = (uint32_t *) malloc(sizeof(uint32_t) * 128);
    if (!buffer_512)
        print_error("%s", "kontbl");

    /* Begin parsing the MIDI */
    printf("\nInput  = %s\n", input_file_name);
    printf("Output = %s\n\n", output_file_name);

    /* Open files and set up exit function */
    input_file_fp = fopen(input_file_name, "rb");
    if (!input_file_fp)
        print_error("%s", input_file_name);
    output_file_fp = fopen(output_file_name, "wt");
    if (!output_file_fp)
        print_error("%s", output_file_name);
    atexit(clean_up);

    /* Generate the outfile file */
    parse_midi_header();
    print_sfile_header();
    print_sfile_body();
    print_sfile_footer();

    /* Handle IO errors */
    if (ferror(output_file_fp))
        print_error("%s", output_file_name);
    if (fclose(output_file_fp))
        print_error("%s", output_file_name);
    if (ferror(input_file_fp))
        print_error("%s", input_file_name);
    if (fclose(input_file_fp))
        print_error("%s", input_file_name);

    /* Exit */
    printf("\n%s", "MID2AGB - Completed, No problem.\n");
    return 0;
}