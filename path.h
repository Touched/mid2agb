#ifndef MID2AGB_PATH_H_
#define MID2AGB_PATH_H_

void *tokenize_path(const char *fullPath);

char *resolve_path_and_extension(char *fullPath, const char *ext);

int check_extension(const char *fullPath, const char *a2);

char *strip_extension(const char *fullPath);

#endif /* MID2AGB_PATH_H_ */