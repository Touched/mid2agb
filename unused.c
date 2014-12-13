
signed int sub_401980(int a1) {
    int v1; // eax@1
    signed int v2; // ebx@1
    int v3; // edi@1
    int v4; // eax@5
    int v5; // ebp@12
    int v6; // edi@12
    signed int result; // eax@20
    const char *v8; // edx@22
    int v9; // [sp-4h] [bp-38h]@22
    int v10; // [sp+10h] [bp-24h]@1
    char Dest; // [sp+14h] [bp-20h]@6
    const char v12[8]; // [sp+1Ch] [bp-18h]@9
    char v13; // [sp+24h] [bp-10h]@26
    char ArgList; // [sp+2Ch] [bp-8h]@24

    v2 = *(_BYTE * )(a1 + 4) - dword_40DEE0 - 64;
    v3 = -1;
    v1 = *(_DWORD * )(a1 + 8);
    v10 = *(_DWORD * ) & note_parameter_lookuptable[4 * *(_BYTE * )(a1 + 5)];
    if (v1 != -1)
        v3 = note_duration_lookuptable[v1];
    if (exact_gate_time && v3 != -1 && (v4 = v1 - v3) != 0)
        sprintf(&Dest, ", gtp%u", v4);
    else
        Dest = 0;
    if (v3 == -1)
        sprintf((char *) v12, "TIE   ");
    else
        sprintf((char *) v12, "N%02u   ", v3);
    if (compression_flag) {
        v6 = dword_40DF1C - v2;
        v5 = dword_40DEF0 - v10;
    }
    else {
        v6 = -1;
        v5 = -1;
    }
    if (dword_40DF00)
        dword_40DF00 = 0;
    else
        byte_40DF28 = 0;
    if (v6 || v5 || Dest) {
        dword_40DF1C = v2;
        if (v2 >= 24) {
            v9 = v2 / 12 - 2;
            v8 = (&off_40C358)[4 * v2 % 12];
        }
        else {
            v9 = v2 / -12 + 2;
            v8 = (&off_40C388)[4 * v2 % 12];
        }
        sprintf(&ArgList, v8, v9);
        if (v5 || Dest) {
            dword_40DEF0 = v10;
            sprintf(&v13, ", v%03u", v10);
        }
        else {
            v13 = 0;
        }
        result = sub_402840((signed int *) a1, v12, "%s%s%s", &ArgList, &v13, &Dest);
    }
    else {
        result = sub_402840((signed int *) a1, v12, 0);
    }
    dword_40DF08 = v6;
    dword_40DF0C = v5;
    return result;
}
// 40C1D0: using guessed type int note_duration_lookuptable[];
// 40CEDC: using guessed type int exact_gate_time;
// 40CEE0: using guessed type int compression_flag;
// 40DEE0: using guessed type int dword_40DEE0;
// 40DEF0: using guessed type int dword_40DEF0;
// 40DF00: using guessed type int dword_40DF00;
// 40DF08: using guessed type int dword_40DF08;
// 40DF0C: using guessed type int dword_40DF0C;
// 40DF1C: using guessed type int dword_40DF1C;
// 40DF28: using guessed type char byte_40DF28;

//----- (00401B40) --------------------------------------------------------
signed int sub_401B40(int a1) {
    signed int v1; // ecx@1
    int v2; // esi@1
    signed int result; // eax@6

    v1 = *(_BYTE * )(a1 + 5) - dword_40DEE0;
    v2 = dword_40DF1C - v1;
    if (dword_40DF1C == v1 || !dword_40DF08)
        byte_40DF28 = 0;
    if (dword_40DF1C == v1 && compression_flag) {
        result = sub_402840((signed int *) a1, "EOT   ", 0);
        dword_40DF08 = v2;
    }
    else {
        dword_40DF1C = v1;
        if (v1 >= 24) {
            result = sub_402840((signed int *) a1, "EOT   ", (&off_40C358)[4 * v1 % 12], v1 / 12 - 2);
            dword_40DF08 = v2;
        }
        else {
            result = sub_402840((signed int *) a1, "EOT   ", (&off_40C388)[4 * v1 % 12], v1 / -12 + 2);
            dword_40DF08 = v2;
        }
    }
    return result;
}
// 40CEE0: using guessed type int compression_flag;
// 40DEE0: using guessed type int dword_40DEE0;
// 40DF08: using guessed type int dword_40DF08;
// 40DF1C: using guessed type int dword_40DF1C;
// 40DF28: using guessed type char byte_40DF28;

//----- (00401C10) --------------------------------------------------------
signed int sub_401C10(int a1) {
    signed int v1; // eax@1
    signed int result; // eax@5

    v1 = *(_BYTE * )(a1 + 5);
    if (v1 >= 42) {
        if (v1 < 64)
            v1 -= 30;
    }
    switch (v1) {
        default:
            result = sub_402A10(*(_DWORD *) a1);
            break;
        case 1:
            result = sub_402840((signed int *) a1, "MOD   ", "%u", *(_DWORD * )(a1 + 8));
            break;
        case 7:
            result = sub_402840((signed int *) a1, "VOL   ", "%u*%s_mvl/mxv", *(_DWORD * )(a1 + 8), *(_DWORD *) ArgList);
            break;
        case 10:
            result = sub_402840((signed int *) a1, "PAN   ", "c_v%+d", *(_DWORD * )(a1 + 8) - 64);
            break;
        case 12:
        case 16:
            result = sub_402060(a1);
            break;
        case 13:
            dword_40DF18 = *(_DWORD * )(a1 + 8);
            result = sub_402A10(*(_DWORD *) a1);
            break;
        case 14:
            *(_DWORD *) dword_40DF10 = *(_DWORD * )(a1 + 8);
            result = sub_402A10(*(_DWORD *) a1);
            break;
        case 15:
            dword_40DF14 = *(_DWORD * )(a1 + 8);
            result = sub_402A10(*(_DWORD *) a1);
            break;
        case 17:
            fprintf(output_file_fp, "%s_%u_L%u:\n", *(_DWORD *) ArgList, sfile_num_tracks, *(_DWORD * )(a1 + 8));
            sub_402A10(*(_DWORD *) a1);
            result = reset_something();
            break;
        case 20:
            result = sub_402840((signed int *) a1, "BENDR ", "%u", *(_DWORD * )(a1 + 8));
            break;
        case 21:
            result = sub_402840((signed int *) a1, "LFOS  ", "%u", *(_DWORD * )(a1 + 8));
            break;
        case 22:
            result = sub_402840((signed int *) a1, "MODT  ", "%u", *(_DWORD * )(a1 + 8));
            break;
        case 24:
            result = sub_402840((signed int *) a1, "TUNE  ", "c_v%+d", *(_DWORD * )(a1 + 8) - 64);
            break;
        case 26:
            result = sub_402840((signed int *) a1, "LFODL ", "%u", *(_DWORD * )(a1 + 8));
            break;
        case 29:
        case 31:
            result = sub_401E60(a1);
            break;
        case 30:
            dword_40DEF8 = *(_DWORD * )(a1 + 8);
            result = sub_401FD0((signed int *) a1);
            break;
        case 33:
        case 39:
            fprintf_and_reset("PRIO  , %u", *(_DWORD * )(a1 + 8));
            result = sub_402A10(*(_DWORD *) a1);
            break;
    }
    return result;
}
// 40DEB8: using guessed type int sfile_num_tracks;
// 40DEF8: using guessed type int dword_40DEF8;
// 40DF14: using guessed type int dword_40DF14;
// 40DF18: using guessed type int dword_40DF18;

//----- (00401E60) --------------------------------------------------------
signed int sub_401E60(int a1) {
    signed int result; // eax@2

    switch (dword_40DEF8) {
        default:
            result = sub_402A10(*(_DWORD *) a1);
            break;
        case 1:
            result = sub_402840((signed int *) a1, "XCMD  ", "xWAVE , %u", *(_DWORD * )(a1 + 8));
            break;
        case 2:
            result = sub_402840((signed int *) a1, "XCMD  ", "xTYPE , %u", *(_DWORD * )(a1 + 8));
            break;
        case 4:
            result = sub_402840((signed int *) a1, "XCMD  ", "xATTA , %u", *(_DWORD * )(a1 + 8));
            break;
        case 5:
            result = sub_402840((signed int *) a1, "XCMD  ", "xDECA , %u", *(_DWORD * )(a1 + 8));
            break;
        case 6:
            result = sub_402840((signed int *) a1, "XCMD  ", "xSUST , %u", *(_DWORD * )(a1 + 8));
            break;
        case 7:
            result = sub_402840((signed int *) a1, "XCMD  ", "xRELE , %u", *(_DWORD * )(a1 + 8));
            break;
        case 8:
            result = sub_402840((signed int *) a1, "XCMD  ", "xIECV , %u", *(_DWORD * )(a1 + 8));
            break;
        case 9:
            result = sub_402840((signed int *) a1, "XCMD  ", "xIECL , %u", *(_DWORD * )(a1 + 8));
            break;
        case 10:
            result = sub_402840((signed int *) a1, "XCMD  ", "xLENG , %u", *(_DWORD * )(a1 + 8));
            break;
        case 11:
            result = sub_402840((signed int *) a1, "XCMD  ", "xSWEE , %u", *(_DWORD * )(a1 + 8));
            break;
    }
    return result;
}
// 40DEF8: using guessed type int dword_40DEF8;

//----- (00401FD0) --------------------------------------------------------
int sub_401FD0(signed int *a1) {
    int result; // eax@3

    if (dword_40DEF8 == 100) {
        fprintf(output_file_fp, "%s_%u_LOOP:\n", *(_DWORD *) ArgList, sfile_num_tracks);
        sub_402A10(*a1);
        result = reset_something();
    }
    else {
        if (dword_40DEF8 == 101) {
            fprintf_and_reset("GOTO");
            sub_4029C0("%s_%u_LOOP", *(_DWORD *) ArgList, sfile_num_tracks);
            result = sub_402A10(*a1);
        }
        else {
            result = sub_402A10(*a1);
        }
    }
    return result;
}
// 40DEB8: using guessed type int sfile_num_tracks;
// 40DEF8: using guessed type int dword_40DEF8;

//----- (00402060) --------------------------------------------------------
signed int sub_402060(int a1) {
    int v1; // esi@2
    char Dest; // [sp+4h] [bp-10h]@8

    switch (dword_40DF18) {
        case 0:
            v1 = a1;
            fprintf_and_reset("MEMACC, mem_set, 0x%02X, %u", *(_DWORD *) dword_40DF10, *(_DWORD * )(a1 + 8));
            break;
        case 1:
            v1 = a1;
            fprintf_and_reset("MEMACC, mem_add, 0x%02X, %u", *(_DWORD *) dword_40DF10, *(_DWORD * )(a1 + 8));
            break;
        case 2:
            v1 = a1;
            fprintf_and_reset("MEMACC, mem_sub, 0x%02X, %u", *(_DWORD *) dword_40DF10, *(_DWORD * )(a1 + 8));
            break;
        case 3:
            v1 = a1;
            fprintf_and_reset("MEMACC, mem_mem_set, 0x%02X, 0x%02X", *(_DWORD *) dword_40DF10, *(_DWORD * )(a1 + 8));
            break;
        case 4:
            v1 = a1;
            fprintf_and_reset("MEMACC, mem_mem_add, 0x%02X, 0x%02X", *(_DWORD *) dword_40DF10, *(_DWORD * )(a1 + 8));
            break;
        case 5:
            v1 = a1;
            fprintf_and_reset("MEMACC, mem_mem_sub, 0x%02X, 0x%02X", *(_DWORD *) dword_40DF10, *(_DWORD * )(a1 + 8));
            break;
        case 6:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "beq", (int) &Dest, (int) "L");
            break;
        case 7:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "bne", (int) &Dest, (int) "L");
            break;
        case 8:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "bhi", (int) &Dest, (int) "L");
            break;
        case 9:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "bhs", (int) &Dest, (int) "L");
            break;
        case 10:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "bls", (int) &Dest, (int) "L");
            break;
        case 11:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "blo", (int) &Dest, (int) "L");
            break;
        case 12:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_beq", (int) &Dest, (int) "L");
            break;
        case 13:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_bne", (int) &Dest, (int) "L");
            break;
        case 14:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_bhi", (int) &Dest, (int) "L");
            break;
        case 15:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_bhs", (int) &Dest, (int) "L");
            break;
        case 16:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_bls", (int) &Dest, (int) "L");
            break;
        case 17:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_blo", (int) &Dest, (int) "L");
            break;
        case 70:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "beq", (int) &Dest, (int) "B");
            break;
        case 71:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "bne", (int) &Dest, (int) "B");
            break;
        case 72:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "bhi", (int) &Dest, (int) "B");
            break;
        case 73:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "bhs", (int) &Dest, (int) "B");
            break;
        case 74:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "bls", (int) &Dest, (int) "B");
            break;
        case 75:
            v1 = a1;
            sprintf(&Dest, "%u", *(_DWORD * )(a1 + 8));
            sub_402740((int) "blo", (int) &Dest, (int) "B");
            break;
        case 76:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_beq", (int) &Dest, (int) "B");
            break;
        case 77:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_bne", (int) &Dest, (int) "B");
            break;
        case 78:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_bhi", (int) &Dest, (int) "B");
            break;
        case 79:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_bhs", (int) &Dest, (int) "B");
            break;
        case 80:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_bls", (int) &Dest, (int) "B");
            break;
        case 81:
            v1 = a1;
            sprintf(&Dest, "0x%02X", *(_DWORD * )(a1 + 8));
            sub_402740((int) "mem_blo", (int) &Dest, (int) "B");
            break;
        default:
            v1 = a1;
            break;
    }
    return sub_402A10(*(_DWORD *) v1);
}
// 40DF18: using guessed type int dword_40DF18;

//----- (00402740) --------------------------------------------------------
int sub_402740(int ArgList, int a2, int a3) {
    fprintf_and_reset("MEMACC, mem_%s, 0x%02X, %s", ArgList, *(_DWORD *) dword_40DF10, a2);
    return sub_4029C0("%s_%u_%s%u", *(_DWORD * )
    ::ArgList, sfile_num_tracks, a3, dword_40DF14);
}
// 40DEB8: using guessed type int sfile_num_tracks;
// 40DF14: using guessed type int dword_40DF14;

//----- (00402790) --------------------------------------------------------
int sub_402790(int a1) {
    signed int v1; // eax@2
    int v2; // edx@3
    int result; // eax@9

    dword_40DEFC = *(_BYTE * )(a1 + 5) + 1;
    fprintf(output_file_fp, "%s_%u_B%u:\n", *(_DWORD *) ArgList, sfile_num_tracks, dword_40DEFC);
    if (sfile_num_tracks == 1) {
        v1 = 0;
        if (!*(_DWORD *) a1) {
            v2 = a1 + 16;
            while (*(_BYTE *) v2 != 21) {
                v2 += 12;
                ++v1;
                if (*(_DWORD * )(v2 - 16))
                    goto LABEL_8;
            }
            v1 = -1;
        }
        LABEL_8:
        if (v1 < 0) {
            sub_402A10(*(_DWORD *) a1);
            result = reset_something();
        }
        else {
            sub_402830((signed int *) a1);
            result = reset_something();
        }
    }
    else {
        sub_402A10(*(_DWORD *) a1);
        result = reset_something();
    }
    return result;
}
// 40DEB8: using guessed type int sfile_num_tracks;
// 40DEFC: using guessed type int dword_40DEFC;

//----- (00402830) --------------------------------------------------------
signed int sub_402830(signed int *a1) {
    return sub_402A10(*a1);
}

//----- (00402840) --------------------------------------------------------
signed int sub_402840(signed int *a1, const char *a2, const char *Format, ...) {
    va_list va; // [sp+18h] [bp+10h]@1

    va_start(va, Format);
    fprintf(output_file_fp, "\t.byte\t\t");
    if (Format) {
        if (strcmp(a2, &byte_40DF28) || !compression_flag) {
            fprintf(output_file_fp, "%s, ", a2);
            strcpy(&byte_40DF28, a2);
        }
        else {
            fprintf(output_file_fp, "        ");
        }
        vfprintf(output_file_fp, Format, va);
    }
    else {
        fprintf(output_file_fp, "%s", a2);
        strcpy(&byte_40DF28, a2);
    }
    fprintf(output_file_fp, "\n");
    return sub_402A10(*a1);
}
// 40CEE0: using guessed type int compression_flag;
// 40DF28: using guessed type char byte_40DF28;

//----- (00402960) --------------------------------------------------------

// 40DF00: using guessed type int dword_40DF00;
// 40DF08: using guessed type int dword_40DF08;
// 40DF0C: using guessed type int dword_40DF0C;

//----- (004029C0) --------------------------------------------------------
int sub_4029C0(const char *Format, ...) {
    va_list va; // [sp+8h] [bp+8h]@1

    va_start(va, Format);
    fprintf(output_file_fp, "\t .word\t");
    vfprintf(output_file_fp, Format, va);
    return fprintf(output_file_fp, "\n");
}

//----- (00402A10) --------------------------------------------------------
signed int sub_402A10(signed int a1) {
    signed int result; // eax@1

    result = a1;
    if (a1) {
        fprintf(output_file_fp, "\t.byte\tW%02u\n", a1);
        result = -1;
        dword_40DF0C = -1;
        dword_40DF08 = -1;
        dword_40DF00 = -1;
    }
    return result;
}
// 40DF00: using guessed type int dword_40DF00;
// 40DF08: using guessed type int dword_40DF08;
// 40DF0C: using guessed type int dword_40DF0C;

//----- (00402A50) --------------------------------------------------------



// 40DEB4: using guessed type int midi_format_short;
// 40DED8: using guessed type int midi_header_end;
// 40DEE8: using guessed type int midi_time_div;
// 40DEEC: using guessed type int midi_number_of_tracks;

//----- (004030E0) --------------------------------------------------------

// 40CEE0: using guessed type int compression_flag;
// 40DEB0: using guessed type char midi_channel;
// 40DEB8: using guessed type int sfile_num_tracks;
// 40DED8: using guessed type int midi_header_end;
// 40DEE5: using guessed type char negative_one_thing;
// 40DEEC: using guessed type int midi_number_of_tracks;

//----- (004032B0) --------------------------------------------------------


//----- (00403310) --------------------------------------------------------

//----- (004033C0) --------------------------------------------------------

// 40DECC: using guessed type int midi_absolute_time;
// 40DEDC: using guessed type char last_control_event_byte;

//----- (00403410) --------------------------------------------------------


//----- (00403440) --------------------------------------------------------


//----- (004034D0) --------------------------------------------------------


//----- (00403590) --------------------------------------------------------


//----- (00403690) --------------------------------------------------------


//----- (004036E0) --------------------------------------------------------


//----- (00403700) --------------------------------------------------------

// 403700: using guessed type _DWORD   assert_a_leq_b(_DWORD, _DWORD);

//----- (00403720) --------------------------------------------------------

// 403700: using guessed type _DWORD   assert_a_leq_b(_DWORD, _DWORD);

//----- (00403770) --------------------------------------------------------

// 40CED8: using guessed type int clock_per_beat_flag;
// 40DECC: using guessed type int midi_absolute_time;

//----- (00403AD0) --------------------------------------------------------


//----- (00403B70) --------------------------------------------------------

// 40CEE8: using guessed type int sfile_num_blocks;

//----- (00403BA0) --------------------------------------------------------

// 403700: using guessed type _DWORD   assert_a_leq_b(_DWORD, _DWORD);
// 40DEE4: using guessed type char starts_at_zero_thing;
// 40DEE5: using guessed type char negative_one_thing;

//----- (00403C20) --------------------------------------------------------

// 40DEB0: using guessed type char midi_channel;
// 40DECC: using guessed type int midi_absolute_time;
// 40DEE4: using guessed type char starts_at_zero_thing;
// 40DEE5: using guessed type char negative_one_thing;

//----- (00404070) --------------------------------------------------------

// 40DEDC: using guessed type char last_control_event_byte;

//----- (004040F0) --------------------------------------------------------

// 40DEB0: using guessed type char midi_channel;

//----- (004042F0) --------------------------------------------------------


//----- (004043A0) --------------------------------------------------------
Event *swap_event_buffers(Event **first, Event **second) {
    Event *first_copy; // eax@1

    first_copy = *first;
    *first = *second;
    *second = first_copy;
    return first_copy;
}

//----- (004043C0) --------------------------------------------------------
int merge_buffers_maybe(Event *control_events, Event *meta_events, Event *buffer, int amount) {
    int current_event; // esi@1
    Event *meta_event; // ebx@2
    Event *control_event; // ebp@2
    int max_events; // edi@2
    Event *event_out; // ecx@4
    signed int compare_result; // eax@4
    int control_event_time; // edx@5
    int meta_event_time; // edx@6
    Event *control_event2; // ebx@10
    Event *output_control_events; // ebp@11
    int control_events_num; // ST00_4@12
    Event *meta_event2; // ebx@13
    Event *output_meta_events; // ebp@14
    int meta_events_num; // ST00_4@15
    Event *last_event; // ecx@16
    Event *last_meta; // ebx@16
    Event *last_control; // edi@16
    signed int last_compare_res; // eax@16
    int result; // eax@17
    int current_meta_event; // [sp+10h] [bp-8h]@1
    int current_control_event; // [sp+14h] [bp-4h]@1

    current_event = 0;
    current_meta_event = 0;
    current_control_event = 0;
    if (track_end(control_events)) {
        max_events = amount;
    }
    else {
        control_event = control_events;
        meta_event = meta_events;
        max_events = amount;
        do {
            if (track_end(meta_event))
                break;
            assert_a_leq_b(current_event, amount);
            compare_result = compare_event_maybe(control_event, meta_event);
            event_out = &buffer[current_event];
            if (compare_result > 0) {
                meta_event_time = meta_event->time;     // Copy meta event into the output buffer
                ++meta_event;
                event_out->time = meta_event_time;
                ++current_meta_event;
                *(_DWORD * ) & event_out->type = *((_DWORD *) meta_event - 2);// Could just do this before the increment of meta_event
                event_out->param2 = *((_DWORD *) meta_event - 1);
            }
            else {
                control_event_time = control_event->time;// Copy control event into the output buffer
                ++control_event;
                event_out->time = control_event_time;
                ++current_control_event;
                *(_DWORD * ) & event_out->type = *((_DWORD *) control_event - 2);
                event_out->param2 = *((_DWORD *) control_event - 1);
            }
            ++current_event;
        }
        while (!track_end(control_event));
    }
    control_event2 = &control_events[current_control_event];
    if (!track_end(&control_events[current_control_event])) {
        output_control_events = &buffer[current_event];
        do {
            ++control_event2;
            control_events_num = current_event;
            ++output_control_events;
            ++current_event;
            assert_a_leq_b(control_events_num, max_events);
            ++current_control_event;
            output_control_events[-1].time = control_event2[-1].time;
            *((_DWORD *) output_control_events - 2) = *((_DWORD *) control_event2 - 2);
            *((_DWORD *) output_control_events - 1) = *((_DWORD *) control_event2 - 1);
        }
        while (!track_end(control_event2));
    }
    meta_event2 = &meta_events[current_meta_event];
    if (!track_end(&meta_events[current_meta_event])) {
        output_meta_events = &buffer[current_event];
        do {
            ++meta_event2;
            meta_events_num = current_event;
            ++output_meta_events;
            ++current_event;
            assert_a_leq_b(meta_events_num, max_events);
            ++current_meta_event;
            output_meta_events[-1].time = meta_event2[-1].time;
            *((_DWORD *) output_meta_events - 2) = *((_DWORD *) meta_event2 - 2);
            *((_DWORD *) output_meta_events - 1) = *((_DWORD *) meta_event2 - 1);
        }
        while (!track_end(meta_event2));
    }
    assert_a_leq_b(current_event, max_events);
    last_meta = &meta_events[current_meta_event];
    last_control = &control_events[current_control_event];
    last_compare_res = compare_event_maybe(&control_events[current_control_event], &meta_events[current_meta_event]);
    last_event = &buffer[current_event];
    if (last_compare_res <= 0) {
        last_event->time = last_meta->time;
        result = *(_DWORD * ) & last_meta->type;
        *(_DWORD * ) & last_event->type = result;
        last_event->param2 = last_meta->param2;
    }
    else {
        last_event->time = last_control->time;
        result = *(_DWORD * ) & last_control->type;
        *(_DWORD * ) & last_event->type = result;
        last_event->param2 = last_control->param2;
    }
    return result;
}
// 403700: using guessed type _DWORD   assert_a_leq_b(_DWORD, _DWORD);

//----- (00404590) --------------------------------------------------------
int sub_404590(int a1) {
    int v1; // edi@2
    int v2; // ebx@3
    int v3; // edx@3
    int v4; // ebx@3
    int v5; // ebp@4
    int v6; // ecx@6
    int v7; // eax@6
    int v8; // ecx@7
    int v9; // ebx@7
    int v10; // edx@7
    int result; // eax@8
    int v12; // ebx@8
    int v13; // edi@9
    Event *v14; // ebp@10
    int v15; // ecx@12
    int v16; // eax@12
    int v17; // edx@13
    int v18; // [sp+10h] [bp-10h]@1
    Event control_event; // [sp+14h] [bp-Ch]@3
    int v20; // [sp+18h] [bp-8h]@3
    int v21; // [sp+1Ch] [bp-4h]@3

    v18 = 0;
    if (!track_end((Event *) a1)) {
        v1 = a1;
        do {
            v3 = *(_DWORD * )(v1 + 4);
            v4 = *(_DWORD * )(v1 + 8);
            control_event.time = *(_DWORD *) v1;
            v20 = v3;
            v21 = v4;
            v2 = v18 - 1;
            if (v18 - 1 >= 0) {
                v5 = a1 + 12 * v2;
                do {
                    if (compare_event_maybe(&control_event, (Event *) v5) >= 0)
                        break;
                    v6 = v5 + 12;
                    v7 = *(_DWORD *) v5;
                    v5 -= 12;
                    --v2;
                    *(_DWORD *) v6 = v7;
                    *(_DWORD * )(v6 + 4) = *(_DWORD * )(v5 + 16);
                    *(_DWORD * )(v6 + 8) = *(_DWORD * )(v5 + 20);
                }
                while (v2 >= 0);
            }
            v8 = a1 + 12 * v2 + 12;
            v9 = v20;
            v10 = v21;
            v1 += 12;
            *(_DWORD *) v8 = control_event.time;
            *(_DWORD * )(v8 + 4) = v9;
            ++v18;
            *(_DWORD * )(v8 + 8) = v10;
        }
        while (!track_end((Event *) v1));
    }
    v12 = 0;
    result = track_end((Event *) a1);
    if (!result) {
        v13 = a1;
        do {
            v14 = (Event * )(a1 + 12 * v12);
            if (!compare_event_maybe((Event *) v13, (Event * )(a1 + 12 * v12))) {
                do {
                    ++v14;
                    ++v12;
                }
                while (!compare_event_maybe((Event *) v13, v14));
                v15 = a1 + 12 * v12;
                v16 = *(_DWORD * )(v15 - 12);
                v15 -= 12;
                *(_DWORD *) v13 = v16;
                *(_DWORD * )(v13 + 4) = *(_DWORD * )(v15 + 4);
                *(_DWORD * )(v13 + 8) = *(_DWORD * )(v15 + 8);
            }
            v17 = a1 + 12 * v12++;
            v13 += 12;
            *(_DWORD *) v13 = *(_DWORD *) v17;
            *(_DWORD * )(v13 + 4) = *(_DWORD * )(v17 + 4);
            *(_DWORD * )(v13 + 8) = *(_DWORD * )(v17 + 8);
            result = track_end((Event *) v13);
        }
        while (!result);
    }
    return result;
}

//----- (004046C0) --------------------------------------------------------
int convert_event_times(Event *event) {
    int event_parameter; // ebx@1
    int counter; // edi@1
    int converted_time; // eax@4
    int current_event; // eax@10
    int v5; // eax@10

    counter = 0;
    event_parameter = (int) &event->param2;
    do {
        *(_DWORD * )(event_parameter - 8) = 24 * clock_per_beat_flag * *(_DWORD * )(event_parameter - 8) / midi_time_div;
        if (is_music_note_event((Event * )(event_parameter - 8))) {
            if (*(_DWORD *) event_parameter != -1) {
                converted_time = 24 * *(_DWORD *) event_parameter * clock_per_beat_flag / midi_time_div;// Work out note duration, presumably
                *(_DWORD *) event_parameter = converted_time;
                if (!converted_time)
                    *(_DWORD *) event_parameter = 1;
                if (!exact_gate_time) {
                    if (*(_DWORD *) event_parameter < 96)
                        *(_DWORD *) event_parameter = note_duration_lookuptable[*(_DWORD *) event_parameter];
                }
            }
            *(_BYTE * )(event_parameter - 3) = note_parameter_lookuptable[4 * *(_BYTE * )(event_parameter - 3)];
        }
        v5 = counter;
        event_parameter += 12;
        ++counter;
        current_event = track_end(&event[v5]);
    }
    while (!current_event);
    return current_event;
}
// 40C1D0: using guessed type int note_duration_lookuptable[];
// 40CED8: using guessed type int clock_per_beat_flag;
// 40CEDC: using guessed type int exact_gate_time;
// 40DEE8: using guessed type int midi_time_div;

//----- (00404770) --------------------------------------------------------
int adjust_times_something(Event *events_buffer, Event *control_events, int max_events) {
    int counter; // ebx@1
    Event *event; // edi@1
    Event *current_control_event; // ebp@3
    int const24int; // edx@4
    int adjusted; // ecx@4
    Event *event_ptr; // ecx@8
    int result; // eax@10
    int ev_time; // eax@10
    Event *ev_ptr; // ecx@10
    int index; // eax@10
    int ev_param1; // edx@10
    char control_event[4]; // [sp+10h] [bp-10h]@1
    const __int16 const24; // [sp+14h] [bp-Ch]@1
    int adjustment; // [sp+18h] [bp-8h]@1
    int new_length; // [sp+1Ch] [bp-4h]@1

    counter = 0;
    new_length = 0;
    *(_DWORD *) control_event = 0;
    event = events_buffer;
    const24 = 24;
    adjustment = 384 * clock_per_beat_flag >> 2;  // 96 * clock_per_beat_flag
    do {
        assert_a_leq_b(counter, max_events);
        if (compare_event_maybe((Event *) control_event, event) < 0) {
            current_control_event = &control_events[counter];
            do {
                const24int = *(_DWORD * ) & const24;
                ++current_control_event;
                ++counter;
                adjusted = adjustment;
                current_control_event[-1].time = *(_DWORD *) control_event;
                *((_DWORD *) current_control_event - 2) = const24int;// set type
                *((_DWORD *) current_control_event - 1) = adjusted;// param2
                assert_a_leq_b(counter, max_events);
                *(_DWORD *) control_event += adjustment;
            }
            while (compare_event_maybe((Event *) control_event, event) < 0);
        }
        if (event->type == 24) {
            if (sfile_num_tracks == 1) {
                if (event->param2 != adjustment)      // If not adjusted
                {
                    event_ptr = &control_events[counter++];
                    event_ptr->time = event->time;
                    *(_DWORD * ) & event_ptr->type = *(_DWORD * ) & event->type;
                    event_ptr->param2 = event->param2;
                    event_ptr->type = 21;
                    assert_a_leq_b(counter, max_events);
                }
            }
            adjustment = event->param2;
            *(_DWORD *) control_event = adjustment + event->time;
        }
        ev_time = event->time;
        ev_ptr = &control_events[counter++];
        ++event;
        ev_ptr->time = ev_time;
        index = new_length;
        ev_param1 = *((_DWORD *) event - 2);
        ++new_length;
        *(_DWORD * ) & ev_ptr->type = ev_param1;
        ev_ptr->param2 = *((_DWORD *) event - 1);
        result = track_end(&events_buffer[index]);
    }
    while (!result);
    return result;
}
// 403700: using guessed type _DWORD   assert_a_leq_b(_DWORD, _DWORD);
// 40CED8: using guessed type int clock_per_beat_flag;
// 40DEB8: using guessed type int sfile_num_tracks;

//----- (004048B0) --------------------------------------------------------
int mystery1(Event *merged_events, Event *control_events, int max_events) {
    signed int v3; // ebx@1
    int v4; // esi@1
    int v5; // eax@3
    int v6; // edx@5
    Event *v7; // ecx@7
    int v8; // eax@9
    int result; // eax@9
    int v10; // eax@9
    int v11; // [sp+10h] [bp-Ch]@1
    int v12; // [sp+14h] [bp-8h]@1
    int v13; // [sp+18h] [bp-4h]@1

    dword_40DEE0 = 0;
    v12 = 0;
    v13 = 0;
    v11 = 127;
    v3 = 1;
    sub_4049D0(
            (int) merged_events,
            (int) control_events,
            (
    unsigned __int8)negative_one_thing,
    (unsigned __int8)starts_at_zero_thing,
            (int) &v12,
            (int) &v11);
    v4 = (int) merged_events;
    do {
        assert_a_leq_b(v3, max_events);
        if (is_music_note_event((Event *) v4)) {
            v5 = *(_BYTE * )(v4 + 4) - 64;
            if (v12 > v5 || v11 < v5) {
                v6 = 3 * v3++;
                sub_4049D0(v4, (int) ((char *) control_events + 4 * v6), v5, v5, (int) &v12, (int) &v11);
                assert_a_leq_b(v3, max_events);
            }
        }
        else {
            if (*(_BYTE * )(v4 + 4) == 24) {
                v7 = &control_events[v3];
                v7->time = *(_DWORD *) v4;
                v7->type = *(_BYTE * )(v4 + 4);
                v7->param1 = dword_40DEE0;
                goto LABEL_9;
            }
        }
        v7 = &control_events[v3];
        v7->time = *(_DWORD *) v4;
        *(_DWORD * ) & v7->type = *(_DWORD * )(v4 + 4);
        LABEL_9:
        v8 = *(_DWORD * )(v4 + 8);
        ++v3;
        v4 += 12;
        v7->param2 = v8;
        v10 = v13++;
        result = track_end(&merged_events[v10]);
    }
    while (!result);
    return result;
}
// 403700: using guessed type _DWORD   assert_a_leq_b(_DWORD, _DWORD);
// 40DEE0: using guessed type int dword_40DEE0;
// 40DEE4: using guessed type char starts_at_zero_thing;
// 40DEE5: using guessed type char negative_one_thing;

//----- (004049D0) --------------------------------------------------------
int sub_4049D0(int a1, int a2, int a3, int a4, int a5, int a6) {
    signed int v6; // ebx@1
    int v7; // esi@4
    int result; // eax@10
    char v9; // cl@10

    v6 = -12;
    if (a3 >= 0)
        v6 = 12;
    if (*(_DWORD *) a5 < 0) {
        v7 = a6;
    }
    else {
        v7 = a6;
        while (*(_DWORD *) a6 <= 127) {
            if (*(_DWORD *) a5 <= a3 && *(_DWORD *) a6 >= a4) {
                dword_40DEE0 = *(_DWORD *) a5;
                result = *(_DWORD *) a1;
                *(_BYTE * )(a2 + 4) = 49;
                *(_DWORD *) a2 = result;
                v9 = dword_40DEE0;
                *(_DWORD * )(a2 + 8) = 0;
                *(_BYTE * )(a2 + 5) = v9;
                return result;
            }
            *(_DWORD *) a5 += v6;
            *(_DWORD *) a6 += v6;
            if (*(_DWORD *) a5 < 0)
                break;
        }
    }
    result = a1;
    dword_40DEE0 = 0;
    *(_DWORD *) a2 = *(_DWORD *) a1;
    *(_BYTE * )(a2 + 5) = 0;
    *(_BYTE * )(a2 + 4) = 49;
    *(_DWORD * )(a2 + 8) = 0;
    *(_DWORD *) a5 = 0;
    *(_DWORD *) v7 = 127;
    return result;
}
// 40DEE0: using guessed type int dword_40DEE0;

//----- (00404A70) --------------------------------------------------------
int split_note_into_on_off_events_maybe(Event *control_events, Event *merged_events, int max_events) {
    Event *control_event; // ebx@1
    int current_event; // edi@1
    int ptr_offset; // eax@4
    Event *merged_event; // ecx@4
    Event *merged_event3; // ecx@4
    Event *merged_event2; // ecx@5
    int ptr_adjust; // ecx@6
    int index; // [sp+10h] [bp-4h]@1

    control_event = control_events;
    current_event = 0;
    index = 0;
    do {
        assert_a_leq_b(current_event, max_events);
        if (is_music_note_event(control_event) && control_event->param2 > 96) {
            ptr_offset = 3 * current_event++;         // ptr_offset = sizeof(Event) * current_event++
            merged_event = (Event * )((char *) merged_events + 4 * ptr_offset);
            merged_event->time = control_event->time;
            merged_event->type = control_event->type;
            merged_event->param1 = control_event->param1;
            merged_event->param2 = -1;
            assert_a_leq_b(current_event, max_events);
            merged_event3 = &merged_events[current_event];
            merged_event3->time = control_event->time + control_event->param2;
            merged_event3->type = 1;
            merged_event3->param1 = control_event->type - 64;
            merged_event3->param2 = 0;
        }
        else {
            merged_event2 = &merged_events[current_event];
            merged_event2->time = control_event->time;
            *(_DWORD * ) & merged_event2->type = *(_DWORD * ) & control_event->type;
            merged_event2->param2 = control_event->param2;
        }
        ++current_event;
        ptr_adjust = 3 * index;                     // Ends up just being sizeof(Event) * index 
        // (3 * 4 * index = 12 * index)
        ++control_event;
        ++index;
    }
    while (!track_end((Event * )((char *) control_events + 4 * ptr_adjust)));
    return sub_404590((int) merged_events);
}
// 403700: using guessed type _DWORD   assert_a_leq_b(_DWORD, _DWORD);

//----- (00404B40) --------------------------------------------------------
int mystery2(Event *control_events, Event *merged_events, int max_events) {
    int v3; // ebx@1
    int v4; // edi@1
    Event *v5; // ebp@3
    int v7; // edx@5
    int v8; // eax@6
    char *v9; // ecx@6
    int result; // eax@7
    Event *v11; // ebp@7
    Event *v12; // edx@7
    int v13; // eax@7
    int v14; // eax@7
    int v15; // [sp+10h] [bp-10h]@2
    Event *v16; // [sp+14h] [bp-Ch]@1
    unsigned int v17; // [sp+18h] [bp-8h]@3
    int v18; // [sp+1Ch] [bp-4h]@1

    v3 = 0;
    v4 = 0;
    v18 = 0;
    v16 = control_events;
    do {
        assert_a_leq_b(v4, max_events);
        v15 = v16->time - v3;
        if (v15 > 96) {
            v5 = &merged_events[v4];
            v17 = (v15 - 1) / 0x60u;
            v15 += -96 * (v15 - 1) / 0x60u;
            do {
                v3 += 96;
                ++v5;
                ++v4;
                v5[-1].time = v3;
                *((_BYTE *) v5 - 8) = -2;
                *((_BYTE *) v5 - 7) = 0;
                *((_DWORD *) v5 - 1) = 0;
                assert_a_leq_b(v4, max_events);
            }
            while (v17-- != 1);
        }
        v7 = note_duration_lookuptable[v15];
        if (v7 != v15) {
            v8 = 3 * v4++;
            v9 = (char *) merged_events + 4 * v8;
            *(_DWORD *) v9 = v7 + v3;
            v9[4] = -2;
            v9[5] = 0;
            *((_DWORD *) v9 + 2) = 0;
            assert_a_leq_b(v4, max_events);
        }
        v11 = v16;
        v3 = v16->time;
        v12 = &merged_events[v4];
        v13 = v16->time;
        ++v4;
        ++v16;
        v12->time = v13;
        v14 = v18++;
        *(_DWORD * ) & v12->type = *(_DWORD * ) & v11->type;
        v12->param2 = v11->param2;
        result = track_end(&control_events[v14]);
    }
    while (!result);
    return result;
}
// 403700: using guessed type _DWORD   assert_a_leq_b(_DWORD, _DWORD);
// 40C1D0: using guessed type int note_duration_lookuptable[];

//----- (00404C60) --------------------------------------------------------
int remove_tempo_events_from_buffer(Event *meta_events) {
    int new_length; // ebp@1
    Event *meta_event; // edi@1
    int current_meta_event; // esi@1
    int i; // eax@2
    int result; // eax@4
    Event *meta_event_copy; // ecx@4
    int index; // eax@4

    current_meta_event = 0;
    new_length = 0;
    meta_event = meta_events;
    do {
        for (i = (int) &meta_events[current_meta_event].type; *(_BYTE *) i == 25; ++current_meta_event)// Skip tempo events
            i += 12;
        meta_event_copy = &meta_events[current_meta_event++];
        meta_event->time = meta_event_copy->time;
        ++meta_event;
        index = new_length++;
        *((_DWORD *) meta_event - 2) = *(_DWORD * ) & meta_event_copy->type;
        *((_DWORD *) meta_event - 1) = meta_event_copy->param2;
        result = track_end(&meta_events[index]);
    }
    while (!result);
    return result;
}

//----- (00404CC0) --------------------------------------------------------
int increment_counter_when_type24_something(Event *control_events) {
    int result; // eax@1
    Event *control_event; // edi@1
    int counter; // esi@1

    control_event = control_events;
    counter = 0;
    dword_40DEC0 = control_events->time;
    for (result = track_end(control_events); !result; result = track_end(control_event)) {
        control_event->time = control_event[1].time - control_event->time;
        if (control_event->type == 24) {
            control_event->type = 22;
            control_event->param2 = counter++;
        }
        ++control_event;
    }
    return result;
}
// 40DEC0: using guessed type int dword_40DEC0;

//----- (00404D10) --------------------------------------------------------
int compress_events_probably(Event *control_events) {
    Event *i; // esi@2
    int result; // eax@5
    int v3; // esi@5
    int v4; // edi@7
    Event *j; // ebp@8
    int v6; // ebp@11
    int v7; // [sp+10h] [bp-4h]@1

    v7 = 0;
    do {
        for (i = &control_events[v7]; i->type != 22; ++v7) {
            if (track_end(i))
                break;
            ++i;
        }
        v3 = (int) &control_events[v7];
        result = track_end(&control_events[v7]);
        if (result)
            break;
        if (compression_sub1(v3) >= 6) {
            v4 = v7 + 1;
            do {
                for (j = &control_events[v4]; j->type != 22; ++v4) {
                    if (track_end(j))
                        break;
                    ++j;
                }
                v6 = (int) &control_events[v4];
                if (track_end(&control_events[v4]))
                    break;
                if (!compression_sub2(v3, v6)) {
                    *(_BYTE * )(v6 + 4) = 23;
                    *(_DWORD * )(v6 + 8) = *(_DWORD * )(v3 + 8) & 0x7FFFFFFF;
                    *(_DWORD * )(v3 + 8) |= 0x80000000u;
                }
                ++v4;
            }
            while (!track_end((Event *) v6));
        }
        ++v7;
        result = track_end((Event *) v3);
    }
    while (!result);
    return result;
}

//----- (00404E20) --------------------------------------------------------
bool compression_sub1(int a1) {
    char v1; // bl@1
    int v2; // ebp@1
    bool v3; // edi@1
    int i; // esi@1
    signed int v5; // ecx@3
    int v6; // edx@7
    char v8; // [sp+12h] [bp-Eh]@1
    char v9; // [sp+13h] [bp-Dh]@1
    int v10; // [sp+18h] [bp-8h]@1

    v10 = *(_DWORD * )(a1 + 4);
    v9 = -128;
    v1 = *(_DWORD * )(a1 + 4);
    v2 = -2147483648;
    v8 = -128;
    v3 = *(_DWORD *) a1 >= 1u;
    for (i = a1 + 12; !sub_404FF0(i); i += 12) {
        if (is_music_note_event((Event *) i)) {
            v5 = 0;
            if (*(_BYTE * )(i + 4) != v8) {
                v5 = 1;
                v8 = *(_BYTE * )(i + 4);
            }
            if (*(_BYTE * )(i + 5) != v9) {
                ++v5;
                v9 = *(_BYTE * )(i + 5);
            }
            v6 = *(_DWORD * )(i + 8);
            if (note_duration_lookuptable[v6] != v2) {
                ++v5;
                v2 = note_duration_lookuptable[v6];
            }
            if (v6 != v2)
                ++v5;
            if (!v5)
                goto LABEL_20;
            v3 += v5;
        }
        else {
            v2 = -2147483648;
            if (*(_BYTE * )(i + 4) == v1) {
                if (v1 != 34 && v1 != 37 && v1 != 1 || *(_BYTE * )(i + 5) == BYTE1(v10)) {
                    LABEL_20:
                    ++v3;
                    goto LABEL_21;
                }
                v3 += 2;
            }
            else {
                v3 += 2;
            }
        }
        LABEL_21:
        v10 = *(_DWORD * )(i + 4);
        v1 = *(_DWORD * )(i + 4);
        if (*(_DWORD *) i)
            ++v3;
    }
    return v3;
}
// 40C1D0: using guessed type int note_duration_lookuptable[];

//----- (00404F30) --------------------------------------------------------
int compression_sub2(int a1, int a2) {
    int v2; // ebx@4
    signed int v3; // esi@4
    int v4; // edi@5
    int result; // eax@11

    if (*(_BYTE * )(a2 + 4) != *(_BYTE * )(a1 + 4)
            || *(_BYTE * )(a2 + 5) != *(_BYTE * )(a1 + 5)
            || *(_DWORD *) a2 != *(_DWORD *) a1) {
        result = -1;
    }
    else {
        v3 = 1;
        v2 = a1 + 12;
        if (sub_404FF0(a1 + 12)) {
            LABEL_11:
            result = -((unsigned int) sub_404FF0(a2 + 12 * v3) < 1);
        }
        else {
            v4 = a2 + 16;
            while (*(_BYTE * )(v2 + 4) == *(_BYTE *) v4
                    && *(_BYTE * )(v4 + 1) == *(_BYTE * )(v2 + 5)
                    && *(_DWORD * )(v4 + 4) == *(_DWORD * )(v2 + 8)
                    && *(_DWORD * )(v4 - 4) == *(_DWORD *) v2) {
                v2 += 12;
                v4 += 12;
                ++v3;
                if (sub_404FF0(v2))
                    goto LABEL_11;
            }
            result = -1;
        }
    }
    return result;
}

//----- (00404FD0) --------------------------------------------------------
signed int sub_404FD0(int a1) {
    char v1; // al@1
    signed int result; // eax@4

    v1 = *(_BYTE * )(a1 + 4);
    if (v1 == -1 || v1 == 22 || v1 == 23)
        result = -1;
    else
        result = 0;
    return result;
}

//----- (00404FF0) --------------------------------------------------------
signed int sub_404FF0(int a1) {
    signed int result; // eax@3

    if (sub_404FD0(a1) || *(_BYTE * )(a1 + 4) < 0x16u)
        result = -1;
    else
        result = 0;
    return result;
}

//----- (00405C5F) --------------------------------------------------------
int __usercallsub_405C5F<eax>(int a1<ebp>)
{
    *(_DWORD * )(a1 - 28) = ***(_DWORD * **)(a1 - 20);
    return _XcptFilter(*(_DWORD * )(a1 - 28), *(struct _EXCEPTION_POINTERS **) (a1 - 20));
}

//----- (00405C7A) --------------------------------------------------------
void __usercallsub_405C7A(int a1<ebp>)
{
    _exit(*(_DWORD * )(a1 - 28));
}

//----- (004070D0) --------------------------------------------------------
int sub_4070D0() {
    return flsall(1);
}
// 4070E0: using guessed type _DWORD   flsall(_DWORD);

//----- (00407470) --------------------------------------------------------
signed int sub_407470(FILE *File, int a2, int a3) {
    int v3; // ebx@1
    unsigned __int8
    v4; // al@2
    int v5; // eax@4
    __int16 v6; // ax@5
    int v7; // eax@7
    int v8; // edi@10
    int v9; // esi@10
    int v10; // eax@12
    __int16 v11; // ax@13
    int v12; // eax@28
    unsigned __int8
    v13; // al@34
    int v14; // eax@37
    int *v15; // edi@51
    int v16; // eax@59
    __int16 v17; // ax@60
    int v18; // eax@62
    int v19; // eax@65
    int v20; // eax@68
    __int16 v21; // ax@69
    int v22; // eax@71
    int v23; // eax@76
    int v24; // esi@76
    int v25; // eax@77
    int v26; // eax@80
    int v27; // eax@84
    __int16 v28; // ax@85
    int v29; // eax@87
    int v30; // ST08_4@91
    int v31; // eax@113
    unsigned __int8
    v32; // cl@113
    char v33; // al@115
    unsigned __int8
    i; // al@119
    char v35; // cl@120
    int v36; // edi@127
    int v37; // eax@129
    signed int v38; // eax@130
    int v39; // ecx@136
    int v40; // ecx@137
    int v41; // eax@157
    int v42; // eax@162
    int v43; // eax@167
    __int16 v44; // ax@168
    int v45; // eax@172
    __int16 v46; // ax@173
    __int64 v47; // ST00_8@178
    int v48; // eax@193
    __int16 v49; // ax@194
    int v50; // eax@201
    __int16 v51; // ax@202
    int v52; // edx@221
    int v53; // ecx@221
    int v54; // esi@226
    int v55; // eax@228
    int v56; // esi@228
    signed int result; // eax@239
    char v58; // [sp+11h] [bp-1BFh]@1
    char v59; // [sp+12h] [bp-1BEh]@10
    char v60; // [sp+13h] [bp-1BDh]@10
    char v61; // [sp+14h] [bp-1BCh]@10
    char v62; // [sp+15h] [bp-1BBh]@10
    char v63; // [sp+16h] [bp-1BAh]@10
    char v64; // [sp+17h] [bp-1B9h]@10
    char v65; // [sp+17h] [bp-1B9h]@29
    wchar_t DstCh; // [sp+18h] [bp-1B8h]@136
    char SrcCh; // [sp+1Ah] [bp-1B6h]@134
    char v68; // [sp+1Bh] [bp-1B5h]@135
    int v69; // [sp+1Ch] [bp-1B4h]@1
    int v70; // [sp+20h] [bp-1B0h]@11
    int v71; // [sp+24h] [bp-1ACh]@10
    int v72; // [sp+28h] [bp-1A8h]@10
    int v73; // [sp+2Ch] [bp-1A4h]@28
    __int64 v74; // [sp+30h] [bp-1A0h]@20
    bool v75; // [sp+38h] [bp-198h]@10
    int v76; // [sp+3Ch] [bp-194h]@10
    int v77; // [sp+40h] [bp-190h]@10
    int v78; // [sp+44h] [bp-18Ch]@117
    int v79; // [sp+48h] [bp-188h]@1
    int v80; // [sp+4Ch] [bp-184h]@28
    char v81[11]; // [sp+50h] [bp-180h]@109
    char v82; // [sp+5Bh] [bp-175h]@111
    int C; // [sp+70h] [bp-160h]@1

    v58 = 0;
    v69 = 0;
    v79 = 0;
    v3 = C;
    do {
        v4 = *(_BYTE *) a2;
        if (!*(_BYTE *) a2)
            break;
        if ((signed int) SrcSizeInBytes <= 1) {
            v6 = *((_WORD *) off_40D568 + v4);
            v5 = v6 & 8;
        }
        else {
            v5 = _isctype(v4, 8);
        }
        if (v5) {
            --v69;
            v7 = _whiteout((int) &v69, File);
            _un_inc(v7, File);
            do
                ++a2;
            while (isspace(*(_BYTE *) a2));
        }
        if (*(_BYTE *) a2 == 37) {
            v8 = 0;
            v9 = 0;
            v77 = 0;
            v76 = 0;
            v63 = 0;
            LOBYTE(v75) = 0;
            v59 = 0;
            v62 = 0;
            v64 = 0;
            v60 = 0;
            LOBYTE(v71) = 0;
            v61 = 1;
            v72 = 0;
            do {
                ++a2;
                v70 = *(_BYTE *) a2;
                if ((signed int) SrcSizeInBytes <= 1) {
                    v11 = *((_WORD *) off_40D568 +(
                    unsigned __int8)v70);
                    v10 = v11 & 4;
                }
                else {
                    v10 = _isctype((
                    unsigned __int8)v70, 4);
                }
                if (v10) {
                    ++v76;
                    v9 = v70 + 10 * v9 - 48;
                }
                else {
                    switch (v70) {
                        case 42:
                            ++v62;
                            break;
                        case 73:
                            if (*(_BYTE * )(a2 + 1) != 54 || *(_BYTE * )(a2 + 2) != 52)
                                goto LABEL_25;
                            a2 += 2;
                            ++v72;
                            v74 = 0i64;
                            break;
                        case 76:
                            ++v61;
                            break;
                        case 104:
                            --v61;
                            LOBYTE(v71) = v71 - 1;
                            break;
                        case 108:
                            ++v61;
                            goto LABEL_24;
                        case 119:
                        LABEL_24:
                            LOBYTE(v71) = v71 + 1;
                            break;
                        default:
                        LABEL_25:
                            ++v64;
                            break;
                        case 70:
                        case 78:
                            break;
                    }
                }
            }
            while (!v64);
            if (!v62) {
                v12 = a3;
                a3 += 4;
                v80 = v12;
                v73 = *(_DWORD * )(a3 - 4);
            }
            v65 = 0;
            if (!(_BYTE) v71) {
                if (*(_BYTE *) a2 == 83 || *(_BYTE *) a2 == 67)
                    LOBYTE(v71) = v71 + 1;
                else
                    LOBYTE(v71) = v71 - 1;
            }
            v13 = *(_BYTE *) a2 | 0x20;
            v70 = v13;
            if (v13 != 110) {
                if (v13 == 99 || v13 == 123) {
                    ++v69;
                    v14 = _inc(File);
                }
                else {
                    v14 = _whiteout((int) &v69, File);
                }
                v3 = v14;
            }
            if (v76 && !v9)
                goto LABEL_235;
            switch (v70) {
                default:
                    if (*(_BYTE *) a2 != v3)
                        goto LABEL_235;
                    --v58;
                    if (!v62)
                        a3 = v80;
                    goto LABEL_225;
                case 99:
                    if (!v76) {
                        ++v9;
                        v76 = 1;
                    }
                    if ((_BYTE) v71 > 0)
                        v60 = 1;
                    v72 = (int) "]";
                    goto LABEL_108;
                case 101:
                case 102:
                case 103:
                    v15 = &C;
                    if (v3 == 45) {
                        LOBYTE(C) = 45;
                        v15 = (int *) ((char *) &C + 1);
                    }
                    else {
                        if (v3 != 43)
                            goto LABEL_55;
                    }
                    --v9;
                    ++v69;
                    v3 = _inc(File);
                LABEL_55:
                    if (!v76 || v9 > 349)
                        v9 = 349;
                    while (1) {
                        if ((signed int) SrcSizeInBytes <= 1) {
                            v17 = *((_WORD *) off_40D568 + v3);
                            v16 = v17 & 4;
                        }
                        else {
                            v16 = _isctype(v3, 4);
                        }
                        if (!v16)
                            break;
                        v18 = v9--;
                        if (!v18)
                            break;
                        *(_BYTE *) v15 = v3;
                        v15 = (int *) ((char *) v15 + 1);
                        ++v77;
                        ++v69;
                        v3 = _inc(File);
                    }
                    if (byte_40D778 == (_BYTE) v3) {
                        v19 = v9--;
                        if (v19) {
                            ++v69;
                            v15 = (int *) ((char *) v15 + 1);
                            v3 = _inc(File);
                            *((_BYTE *) v15 - 1) = byte_40D778;
                            while (1) {
                                if ((signed int) SrcSizeInBytes <= 1) {
                                    v21 = *((_WORD *) off_40D568 + v3);
                                    v20 = v21 & 4;
                                }
                                else {
                                    v20 = _isctype(v3, 4);
                                }
                                if (!v20)
                                    break;
                                v22 = v9--;
                                if (!v22)
                                    break;
                                *(_BYTE *) v15 = v3;
                                v15 = (int *) ((char *) v15 + 1);
                                ++v77;
                                ++v69;
                                v3 = _inc(File);
                            }
                        }
                    }
                    if (!v77 || v3 != 101 && v3 != 69 || (v23 = v9, v24 = v9 - 1, !v23))
                        goto LABEL_89;
                    *(_BYTE *) v15 = 101;
                    v15 = (int *) ((char *) v15 + 1);
                    ++v69;
                    v25 = _inc(File);
                    v3 = v25;
                    if (v25 == 45) {
                        *(_BYTE *) v15 = 45;
                        v15 = (int *) ((char *) v15 + 1);
                    }
                    else {
                        if (v25 != 43)
                            goto LABEL_83;
                    }
                    v26 = v24--;
                    if (v26)
                        goto LABEL_82;
                    ++v24;
                LABEL_83:
                    while (1) {
                        if ((signed int) SrcSizeInBytes <= 1) {
                            v28 = *((_WORD *) off_40D568 + v3);
                            v27 = v28 & 4;
                        }
                        else {
                            v27 = _isctype(v3, 4);
                        }
                        if (!v27)
                            break;
                        v29 = v24--;
                        if (!v29)
                            break;
                        *(_BYTE *) v15 = v3;
                        v15 = (int *) ((char *) v15 + 1);
                        ++v77;
                        LABEL_82:
                        ++v69;
                        v3 = _inc(File);
                    }
                LABEL_89:
                    --v69;
                    _un_inc(v3, File);
                    if (!v77)
                        goto LABEL_236;
                    if (!v62) {
                        ++v79;
                        v30 = v73;
                        *(_BYTE *) v15 = 0;
                        off_40DCF0(v61 - 1, v30, &C);
                        JUMPOUT(*(int *) loc_40790F);
                    }
                    goto LABEL_225;
                case 105:
                    v70 = 100;
                    goto LABEL_94;
                case 120:
                LABEL_94:
                    if (v3 == 45) {
                        v59 = 1;
                    }
                    else {
                        if (v3 != 43)
                            goto LABEL_156;
                    }
                    --v9;
                    if (v9 || !v76) {
                        ++v69;
                        v3 = _inc(File);
                    }
                    else {
                        v65 = 1;
                    }
                LABEL_156:
                    if (v3 == 48) {
                        ++v69;
                        v41 = _inc(File);
                        v3 = v41;
                        if ((_BYTE) v41 == 120 || (_BYTE) v41 == 88) {
                            ++v69;
                            v42 = _inc(File);
                            v70 = 120;
                            v3 = v42;
                        }
                        else {
                            v77 = 1;
                            if (v70 == 120) {
                                --v69;
                                _un_inc(v41, File);
                                v3 = 48;
                            }
                            else {
                                v70 = 111;
                            }
                        }
                    }
                    goto LABEL_163;
                case 110:
                    v8 = v69;
                    if (!v62)
                        goto LABEL_220;
                    goto LABEL_225;
                case 112:
                    v61 = 1;
                    goto LABEL_99;
                case 100:
                case 111:
                case 117:
                LABEL_99:
                    if (v3 == 45) {
                        v59 = 1;
                    }
                    else {
                        if (v3 != 43)
                            goto LABEL_163;
                    }
                    --v9;
                    if (v9 || !v76) {
                        ++v69;
                        v3 = _inc(File);
                    }
                    else {
                        v65 = 1;
                    }
                LABEL_163:
                    if (v72) {
                        if (v65) {
                            LABEL_187:
                            if (v59)
                                v74 = -v74;
                            goto LABEL_215;
                        }
                        while (1) {
                            if (v70 == 120) {
                                if ((signed int) SrcSizeInBytes <= 1) {
                                    v44 = *((_WORD *) off_40D568 + v3);
                                    v43 = v44 & 0x80;
                                }
                                else {
                                    v43 = _isctype(v3, 128);
                                }
                                if (!v43)
                                    goto LABEL_179;
                                v74 *= 16i64;
                                v3 = _hextodec(v3);
                            }
                            else {
                                if ((signed int) SrcSizeInBytes <= 1) {
                                    v46 = *((_WORD *) off_40D568 + v3);
                                    v45 = v46 & 4;
                                }
                                else {
                                    v45 = _isctype(v3, 4);
                                }
                                if (!v45) {
                                    LABEL_179:
                                    ++v65;
                                    goto LABEL_180;
                                }
                                if (v70 == 111) {
                                    if (v3 >= 56)
                                        goto LABEL_179;
                                    v74 *= 8i64;
                                }
                                else {
                                    v71 = 0;
                                    v78 = 8;
                                    v75 = 2 >= 0xFFFFFFF8u;
                                    HIDWORD(v47) = 2 >= 0xFFFFFFF8u;
                                    LODWORD(v47) = 10;
                                    v74 *= v47;
                                }
                            }
                            LABEL_180:
                            if (v65) {
                                --v69;
                                _un_inc(v3, File);
                            }
                            else {
                                ++v77;
                                v74 += v3 - 48;
                                if (!v76 || (--v9, v9)) {
                                    ++v69;
                                    v3 = _inc(File);
                                }
                                else {
                                    ++v65;
                                }
                            }
                            if (v65)
                                goto LABEL_187;
                        }
                    }
                    while (!v65) {
                        if (v70 == 120 || v70 == 112) {
                            if ((signed int) SrcSizeInBytes <= 1) {
                                v51 = *((_WORD *) off_40D568 + v3);
                                v50 = v51 & 0x80;
                            }
                            else {
                                v50 = _isctype(v3, 128);
                            }
                            if (!v50) {
                                LABEL_205:
                                ++v65;
                                goto LABEL_206;
                            }
                            v8 *= 16;
                            v3 = _hextodec(v3);
                        }
                        else {
                            if ((signed int) SrcSizeInBytes <= 1) {
                                v49 = *((_WORD *) off_40D568 + v3);
                                v48 = v49 & 4;
                            }
                            else {
                                v48 = _isctype(v3, 4);
                            }
                            if (!v48)
                                goto LABEL_205;
                            if (v70 == 111) {
                                if (v3 >= 56)
                                    goto LABEL_205;
                                v8 *= 8;
                            }
                            else {
                                v8 *= 10;
                            }
                        }
                        LABEL_206:
                        if (v65) {
                            --v69;
                            _un_inc(v3, File);
                        }
                        else {
                            v8 = v3 + v8 - 48;
                            ++v77;
                            if (!v76 || (--v9, v9)) {
                                ++v69;
                                v3 = _inc(File);
                            }
                            else {
                                ++v65;
                            }
                        }
                    }
                    if (v59)
                        v8 = -v8;
                LABEL_215:
                    if (v70 == 70)
                        v77 = 0;
                    if (!v77)
                        goto LABEL_236;
                    if (!v62) {
                        ++v79;
                        LABEL_220:
                        if (v72) {
                            v52 = v73;
                            v53 = HIDWORD(v74);
                            *(_DWORD *) v73 = v74;
                            *(_DWORD * )(v52 + 4) = v53;
                        }
                        else {
                            if (v61)
                                *(_DWORD *) v73 = v8;
                            else
                                *(_WORD *) v73 = v8;
                        }
                    }
                LABEL_225:
                    ++v58;
                    ++a2;
                    break;
                case 115:
                    if ((_BYTE) v71 > 0)
                        v60 = 1;
                    v72 = (int) " \t-\r]";
                    goto LABEL_108;
                case 123:
                    if ((_BYTE) v71 > 0)
                        v60 = 1;
                    ++a2;
                    v72 = a2;
                    if (*(_BYTE *) a2 == 94) {
                        v72 = a2 + 1;
                        LABEL_108:
                        LOBYTE(v75) = -1;
                    }
                    memset(v81, 0, 0x20u);
                    if (v70 == 123) {
                        if (*(_BYTE *) v72 == 93) {
                            v63 = 93;
                            v82 = 32;
                            ++v72;
                        }
                    }
                    while (*(_BYTE *) v72 != 93) {
                        v31 = v72++;
                        v32 = *(_BYTE *) v31;
                        if (*(_BYTE *) v31 == 45 && v63 && (v33 = *(_BYTE *) v72, *(_BYTE *) v72 != 93)) {
                            ++v72;
                            if (v63 >= (unsigned __int8)v33 )
                            {
                                LOBYTE(v78) = v63;
                                v63 = v33;
                            }
                            else
                            {
                                LOBYTE(v78) = v33;
                            }
                            for (i = v63; (_BYTE) v78 >= i; v81[v71] |= 1 << v35) {
                                v71 = i >> 3;
                                v35 = i++ & 7;
                            }
                            v63 = 0;
                        }
                        else {
                            v63 = v32;
                            v81[v32 >> 3] |= 1 << (v32 & 7);
                        }
                    }
                    if (!*(_BYTE *) v72)
                        goto LABEL_236;
                    if (v70 == 123)
                        a2 = v72;
                    v36 = v73;
                    --v69;
                    _un_inc(v3, File);
                    while (2) {
                        if (!v76 || (v37 = v9, --v9, v37)) {
                            ++v69;
                            v38 = _inc(File);
                            v3 = v38;
                            if (v38 != -1 && (char) (v75 ^ v81[v38 >> 3]) & (1 << (v38 & 7))) {
                                if (v62) {
                                    ++v36;
                                }
                                else {
                                    if (v60) {
                                        SrcCh = v38;
                                        if (*((_BYTE *) off_40D568 + 2 *(unsigned __int8)v38 + 1) &0x80 )
                                        {
                                            ++v69;
                                            v68 = _inc(File);
                                        }
                                        mbtowc(&DstCh, &SrcCh, SrcSizeInBytes);
                                        v39 = v73;
                                        v73 += 2;
                                        *(_WORD *) v39 = DstCh;
                                    }
                                    else {
                                        v40 = v73++;
                                        *(_BYTE *) v40 = v38;
                                    }
                                }
                                continue;
                            }
                            --v69;
                            _un_inc(v38, File);
                        }
                        break;
                    }
                    if (v36 == v73)
                        goto LABEL_236;
                    if (!v62) {
                        ++v79;
                        if (v70 != 99) {
                            if (v60)
                                *(_WORD *) v73 = 0;
                            else
                                *(_BYTE *) v73 = 0;
                        }
                    }
                    goto LABEL_225;
            }
        }
        else {
            v54 = a2++;
            ++v69;
            v3 = _inc(File);
            if (*(_BYTE *) v54 != v3)
                goto LABEL_235;
            if (*((_BYTE *) off_40D568 + 2 *(unsigned __int8)v3 + 1) &0x80 )
            {
                v56 = a2++;
                ++v69;
                v55 = _inc(File);
                if (*(_BYTE *) v56 != v55) {
                    --v69;
                    _un_inc(v55, File);
                    LABEL_235:
                    --v69;
                    _un_inc(v3, File);
                    break;
                }
                --v69;
            }
        }
    }
    while (v3 != -1 || *(_BYTE *) a2 == 37 && *(_BYTE * )(a2 + 1) == 110);
    LABEL_236:
    if (v3 == -1) {
        if (v79 || v58)
            result = v79;
        else
            result = -1;
    }
    else {
        result = v79;
    }
    return result;
}
// 40790F: using guessed type int   loc_40790F(FILE *File, int, int);
// 40D568: using guessed type void *off_40D568;
// 40D778: using guessed type char byte_40D778;
// 40DCF0: using guessed type int (  *off_40DCF0)(_DWORD, _DWORD, _DWORD);
// 407470: using guessed type char var_180[11];

// ALL OK, 71 function(s) have been successfully decompiled
