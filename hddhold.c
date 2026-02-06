#define __HDDHOLD_VERSION__ "1.1.0"

/*
 * HDDHold - Prevent HDD from sleeping by writing random data.
 * Copyright (C) 2026 TlFoxHuman (TranslucentFoxHuman, 半狐, 半透明狐人間)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
	#include <windows.h>
	char holdfilename[256] = "C:\\hddhold";
	void cp_sleep(int seconds) {
		Sleep(seconds*1000);
	}
#else
	#include <unistd.h>
	char holdfilename[256] = "/hddhold";
	void cp_sleep(int seconds) {
		sleep(seconds);
	}
#endif

unsigned int interval = 4;
unsigned int bytes = 4;


int main(int argc,char **argv) {
	unsigned char *bindata;
	int i;
	for (i=1;i<argc;i++) {
		if (strcmp(argv[i],"-h")==0 || strcmp(argv[i],"--help")==0){
			printf("hddhold - Prevent HDD from sleeping by writting random data to a file.\n"
				   "\n"
				   "Options:\n"
				   "-b <bytes>    : Set size of random data by bytes. (default: 4)\n"
				   "-i <interval> : Set the interval to perform write access in seconds. (default: 4)\n"
				   "-o <filename> : Set the filename to write random data. (default: %s)\n"
				   "-h --help     : Print this help.\n"
				   "-v --version  : Print program version.\n",holdfilename);
			exit(0);
		} else if (strcmp(argv[i],"-v")==0 || strcmp(argv[i],"--version")==0) {
			printf("hddhold %s\n"
				   "Copyright (C) 2026 TlFoxHuman\n"
				   "This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\n"
                   "This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details: <https://www.gnu.org/licenses/>\n"
				   ,__HDDHOLD_VERSION__);
			exit(0);
		} else if (strcmp(argv[i],"-o")==0) {
			if (argc-1 == i) {
				printf("Missing <filename> for option \"-o\"\n");
				exit(1);
			} else {
				if(strlen(argv[i+1])>(sizeof(holdfilename)/sizeof(char))-2) {
					printf("Filename too long.\n");
					exit(2);
				}
				strncpy(holdfilename,argv[i+1],(sizeof(holdfilename)/sizeof(char)));
				holdfilename[(sizeof(holdfilename)/sizeof(char))-1] = 0;
				i++;
			}
		} else if (strcmp(argv[i],"-i")==0) {
			if (argc-1 == i) {
				printf("Missing <seconds> for option \"-i\"\n");
				exit(1);
			} else {
				interval = atoi(argv[i+1]);
				i++;
			}
		} else if (strcmp(argv[i],"-b")==0) {
			if (argc-1 == i) {
				printf("Missing <bytes> for option \"-b\"\n");
				exit(1);
			} else {
				bytes = atoi(argv[i+1]);
				i++;
			}
		}
	}
	srand(time(0));
	bindata = (unsigned char*)malloc(bytes);
	while (1) {
		FILE *fp;
		for (i=0;i<bytes;i++) {
			bindata[i]= (unsigned char)(rand() % 256);
		}
		fp = fopen(holdfilename,"wb");
		if (fp == NULL) {
			printf("Could not open the file: \"%s\"",holdfilename);
			exit(3);
		}
		if (fwrite(bindata,sizeof(unsigned char),bytes,fp) == 0) {
			printf("Could not write to file.");
		}
			fclose(fp);
			cp_sleep(interval);
	}
	return 0;
}
