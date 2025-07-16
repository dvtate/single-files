#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>

#include <ar.h>
// Defined in ar.h
//   Not redefining
/* Archive files start with the ARMAG identifying string.  Then follows a
   `struct ar_hdr', and as many bytes of member file data as its `ar_size'
   member indicates, for each member file.  */
// #define ARMAG	"!<arch>\n"	/* String that begins an archive file.  */
// #define SARMAG	8		/* Size of that string.  */
// #define ARFMAG	"`\n"		/* String in ar_fmag at end of each header.  */
// struct ar_hdr {
// 	char ar_name[16];		/* Member file name, sometimes / terminated. */
// 	char ar_date[12];		/* File date, decimal seconds since Epoch.  */
// 	char ar_uid[6], ar_gid[6];	/* User and group IDs, in ASCII decimal.  */
// 	char ar_mode[8];		/* File mode, in ASCII octal.  */
// 	char ar_size[10];		/* File size, in ASCII decimal.  */
// 	char ar_fmag[2];		/* Always contains ARFMAG.  */
// };


#define AR_NAME_LEN 16
#define AR_SIZE_LEN 10

// Linked list of ar entries
struct ar_entry {
	// Raw Header
	struct ar_hdr header;

	// File name
	char fname[AR_NAME_LEN];

	// Contents of the file
	char* contents;

	// Length of the contents
	long long len;

	// Next node in linked-list
	struct ar_entry* next;
};

// Load ar entries from file
struct ar_entry* read_ar_file(char* fname) {
	FILE* ar_file = fopen(fname, "r");
	if (!ar_file) {
		fprintf(stderr, "Unable to open file %s\n", fname);
		exit(1);
	}

	// use fseek to go the end of the archive
	fseek(ar_file, 0, SEEK_END);

	// use ftell to get the file position (which should be the length of the archive file)
	long ar_size = ftell(ar_file); //tell me what position im at, takes file pointer as arg

	// now go back to the beginning of the archive
	rewind(ar_file);

	// use assert for sanity checking during development
	// assert will exit program if its predicate evaluates to false
	assert(ar_size > 0);

	// we need a position and a remainder
	long position = ftell(ar_file);
	unsigned long remainder = ar_size - position; // how much data is left in the file

	// check size of archive to be sure the header can be read,
	if (remainder < SARMAG) {
		fprintf(stderr, "Specified file %s is too small to be a valid archive! Exiting.\n", fname);
		exit(1);
	}

	// read the archive file identifier, e.g., !<arch>\n
	char arch[SARMAG];
	fread(arch, SARMAG, 1, ar_file);

	// if our buffer is not !<arch>\n, this is not an archive file!
	// after the read, if we have a valid archive file, we should now be at the
	// first archive member header(presuming there is one).
	if (memcmp(arch, ARMAG, SARMAG) != 0) {
		fprintf(stderr, "Archive file %s does not have valid header! Exiting.\n", fname);
		exit(1); // exit with an error code of 1
	}

	// ARMAG -> HEADER1 -> DATA1 -> HEADER2 -> DATA2 ... until end
	position = ftell(ar_file);
	remainder = ar_size - position;
	struct ar_entry* ret = malloc(sizeof (struct ar_entry));
	struct ar_entry* cur = ret;

	while (1) {
		fread(&cur->header, sizeof(cur->header), 1, ar_file);

		// converts from character array to null-terminated C string
		// relies on / at the end of the filename
		memcpy(cur->fname, cur->header.ar_name, AR_NAME_LEN);
		cur->fname[AR_NAME_LEN] = '\0';

		// remove the slash, replace it with a null
		// after this we have a valid file name, e.g. 'file-a.txt'
		assert(strstr(cur->fname, "/"));
		char* slash = strrchr(cur->fname, '/');
		if (slash)
			*slash = '\0';

		// Get file size
		char file_size_str[AR_SIZE_LEN + 1];
		memcpy(file_size_str, cur->header.ar_size, AR_SIZE_LEN);
		file_size_str[AR_SIZE_LEN] = '\0';
		cur->len = atol(file_size_str); // ignores space padding

		// print the name of the archive member and its size
		// printf("%20s %12ld\n", cur->fname, cur->len);

		// Read contents
		cur->contents = malloc(cur->len);
		fread(cur->contents, cur->len, 1, ar_file);

		// Skip padding for odd file size
		if (cur->len % 2)
			fseek(ar_file, 1, SEEK_CUR);

		// our position and compute the remainder
		position = ftell(ar_file);
		remainder = ar_size - position;

		// Make next node or end LL
		if (remainder >= sizeof (cur->header)) {
			cur->next = malloc(sizeof (struct ar_entry));
			cur = cur->next;
		} else {
			cur->next = NULL;
			break;
		}
	}

	// Close file
	fclose(ar_file);
	return ret;
}

// Store ar entries into a file
void write_ar_file(char* fname, struct ar_entry* node) {
	// Check if file already exists or gets created
	const char existed = !access(fname, R_OK | W_OK);

	// Open file, write header
	FILE* f = fopen(fname, "w");
	if (!f) {
		fprintf(stderr, "cannot open file %s\n", fname);
		exit(1);
	}

	fprintf(f, "%s", ARMAG);

	// For each node
	for (; node; node = node->next) {
		// Write header + contents
		fwrite(&node->header, sizeof (node->header), 1, f);
		fwrite(node->contents, node->len, 1, f);

		// Odd len padding
		if (node->len % 2)
			fputc('\n', f);
	}

	fclose(f);

	// Chmod if didn't exist
	if (!existed)
		chmod(fname, 0666);
}


// Genreate permissions mask string
char* file_perm_str(mode_t perm) {
	static char str[10];
	snprintf(str, 10, "%c%c%c%c%c%c%c%c%c",
		(perm & S_IRUSR) ? 'r' : '-', (perm & S_IWUSR) ? 'w' : '-', (perm & S_IXUSR) ? 'x' : '-',
		(perm & S_IRGRP) ? 'r' : '-', (perm & S_IWGRP) ? 'w' : '-', (perm & S_IXGRP) ? 'x' : '-',
		(perm & S_IROTH) ? 'r' : '-', (perm & S_IWOTH) ? 'w' : '-', (perm & S_IXOTH) ? 'x' : '-');
	return str;
}

// Generate time string like original
char* time_str(time_t epoch) {
	static char str[100];
	struct tm ts = *localtime(&epoch);
	strftime(str, 100, "%d %b %d %H:%M %Y", &ts);
	return str;
}

// -t and -v commands
void list_entries(struct ar_entry* node, char verbose) {
	// if (verbose)
	// 	puts("Mode\tuid / gid\tModified Time\tFile Name");

	for (; node; node = node->next) {
		// Print file name + newline
		if (!verbose) {
			printf("%s\n", node->fname);
		} else {
			printf("%s\t%ld/%ld\t%s\t%s\n",
				file_perm_str(strtol(node->header.ar_mode, NULL, 8)),
				atol(node->header.ar_uid),
				atol(node->header.ar_gid),
				time_str(atol(node->header.ar_date)),
				node->fname
			);
		}
	}
}

// Create an ar_entry struct from a file
struct ar_entry* entry_from_file(char* fname) {
	// Stat file
	struct stat st;
	if (lstat(fname, &st) == -1) {
		fprintf(stderr, "Unable to stat() file %s\n", fname);
		exit(1);
	}

	// Create entry
	struct ar_entry* ret = malloc(sizeof (struct ar_entry));
	memset(&ret->header, ' ', sizeof (ret->header));

	// Populate ar_hdr fields from stat
	snprintf(ret->header.ar_uid, sizeof (ret->header.ar_uid), "%d", st.st_uid);
	snprintf(ret->header.ar_gid, sizeof (ret->header.ar_gid), "%d", st.st_gid);
	snprintf(ret->header.ar_mode, sizeof (ret->header.ar_mode), "%o", st.st_mode);
	snprintf(ret->header.ar_size, sizeof (ret->header.ar_size), "%ld", st.st_size);
	snprintf(ret->header.ar_date, sizeof (ret->header.ar_date), "%ld", st.st_mtime);
	ret->len = st.st_size;
	memcpy(ret->header.ar_fmag, ARFMAG, 2);

	// Populate name
	int len = strlen(fname);
	if (len >= AR_NAME_LEN) {
		fprintf(stderr, "File name %s too long, should be less than %d characters, truncating\n", fname, AR_NAME_LEN);
		len = AR_NAME_LEN;
	}
	memcpy(ret->fname, fname, len);
	memcpy(ret->header.ar_name, fname, len);
	ret->header.ar_name[len] = '/';

	// Fix behavior of snprintf
	for (unsigned i = 0; i < sizeof (ret->header); i++)
		if (((char*)&ret->header)[i] == '\0')
			((char*)&ret->header)[i] = ' ';

	// Not linked
	ret->next = NULL;

	// Read file contents into ret->contents
	FILE* f = fopen(fname, "r+");
	if (!f) {
		fprintf(stderr, "Could not open file %s\n", fname);
		exit(1);
	}
	// fseek(f, 0, SEEK_END);
	// long fsize = ftell(f);
	// fseek(f, 0, SEEK_SET);
	ret->contents = malloc(st.st_size + 1);
	fread(ret->contents, st.st_size, 1, f);
	fclose(f);
	ret->contents[st.st_size] = 0;

	return ret;
}

// Write an entry out to disk
void entry_to_file(struct ar_entry* entry) {
	FILE* f = fopen(entry->fname, "w");
	if (!f) {
		fprintf(stderr, "unable to open file %s\n", entry->fname);
		exit(1);
	}

	// Write contents
	fwrite(entry->contents, entry->len, 1, f);
}

// Find last element in the linked list
struct ar_entry* entries_tail(struct ar_entry* node) {
	struct ar_entry* ret;
	while (node) {
		ret = node;
		node = node->next;
	}
	return ret;
}

// Append all the entries from the current directory
struct ar_entry* entries_from_directory(char* archive_name, char* bin_name) {
	// Open current working directory
	char cwd[PATH_MAX];
	if (getcwd(cwd, PATH_MAX) == NULL) {
		fprintf(stderr, "could not getcwd()\n");
		perror("getcwd() error");
		exit(1);
	}
	// printf("cwd: %s\n", cwd);
	DIR* dir = opendir(cwd);
	if (!dir) {
		fprintf(stderr, "could not opendir()\n");
		exit(1);
	}

	struct ar_entry* ret = NULL;
	struct ar_entry* n = NULL;

	// List files in directory
	struct dirent* ent;
	while ((ent = readdir(dir)) != NULL)
		if (ent->d_type == DT_REG
			&& strcmp(ent->d_name, archive_name)
			&& strcmp(ent->d_name, bin_name))
		{
			// printf("adding: %s\n", ent->d_name);
			if (!ret) {
				ret = entry_from_file(ent->d_name);
				n = ret;
			} else {
				n->next = entry_from_file(ent->d_name);
				n = n->next;
			}
		}

	closedir(dir);
	return ret;
}

int main(int argc, char** argv) {
	// Verify arg count
	if (argc < 3) {
		fprintf(stderr, "USAGE: %s <flag> <archive_name> <files...>\n", argv[0]);
		return 1;
	}

	// Extract arguments
	char* cmd = argv[1];
	char* fname = argv[2];

	// Execute command
	if (!strcmp(cmd, "-t")) {
		// Short table of contents
		list_entries(read_ar_file(fname), 0);
	} else if (!strcmp(cmd, "-v")) {
		// Verbose table of contents
		list_entries(read_ar_file(fname), 1);
	} else if (!strcmp(cmd, "-q")) {
		// Append files
		struct ar_entry* ll, * n;
		int start = 3;
		if (!access(fname, R_OK | W_OK)) {
			// Get linked list of entries from file
			ll = read_ar_file(fname);
			n = entries_tail(ll);
		} else {
			// Create new LL of files
			n = ll = entry_from_file(argv[start++]);
		}

		// Append the files to the end of the list
		for (int i = start; i < argc; i++) {
			n->next = entry_from_file(argv[i]);
			n = n->next;
		}

		// Write to disk
		write_ar_file(fname, ll);
	} else if (!strcmp(cmd, "-d")) {
		// Delete files
		struct ar_entry* ll = read_ar_file(fname);
		// For each file argument
		for (int i = 3; i < argc; i++) {
			// Find file
			struct ar_entry* n = ll;
			struct ar_entry* p = NULL;
			for (; n; p = n, n = n->next) {
				// Remove file from ll
				if (!strcmp(n->fname, argv[i])) {
					if (p == NULL)
						ll = n->next;
					else
						p->next = n->next;
					// free(n);
					break;
				} else {}
			}

			// Not found
			if (n == NULL) {
				fprintf(stderr, "File %s not in archive %s\n", argv[i], fname);
				return 1;
			}
		}

		// Write to disk
		write_ar_file(fname, ll);
	} else if (!strcmp(cmd, "-x")) {
		// Extract file(s)
		struct ar_entry* ll = read_ar_file(fname);
		// For each file argument
		for (int i = 3; i < argc; i++) {
			// Find file
			struct ar_entry* n = ll;
			for (; n; n = n->next)
				// Extract file
				if (!strcmp(n->fname, argv[i])) {
					entry_to_file(n);
					break;
				}

			// Not found
			if (n == NULL) {
				fprintf(stderr, "File %s not in archive %s\n", argv[i], fname);
				return 1;
			}
		}
	} else if (!strcmp(cmd, "-A")) {
		// Append all 'regular' files into the archive
		// Get binary name
		char empty[] = "";
		char* bin = argv[0][0] == '.' ? argv[0] + 2 : empty;

		// Get entries from current directory
		struct ar_entry* add = entries_from_directory(bin, argv[2]);
		struct ar_entry* ll;
		if (!access(fname, R_OK | W_OK)) {
			// Append to end of file
			ll = read_ar_file(fname);
			struct ar_entry* tail = entries_tail(ll);
			tail->next = add;
		} else {
			ll = add;
		}

		// Write to disk
		write_ar_file(fname, ll);
	} else {
		fprintf(stderr, "USAGE: %s <flag> <archive_name> <files...>\n", argv[0]);
		return 1;
	}

	return 0;
}
