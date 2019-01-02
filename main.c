#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "md5.h"

#ifndef bool
typedef enum {
	false,
	true
} bool;
#endif

int main(int argc, char *argv[]) {
	int i, n;
	bool isfile = false;
	unsigned char decrypt[16];
	MD5_CTX md5;
	
	if(argc > 1 && strlen(argv[1]) == 2 && !memcmp(argv[1], "-f", 2)) {
		isfile = true;
	}
	
	if(argc == 1 || (argc == 2 && isfile)) {
		fprintf(stderr, "usage:\n    %s -f file ...\n    %s string ...\n", argv[0], argv[0]);
		return 1;
	}
	
	if(isfile) {
		FILE *fp;
		for(n=2; n<argc; n++) {
			fp = fopen(argv[n], "rb");
			if(fp == NULL) {
				fprintf(stderr, "File %s not exists, errno = %d, error = %s\n", argv[n], errno, strerror(errno));
				continue;
			}
			
			MD5Init(&md5);
			
			do {
				unsigned char encrypt[1024];
				while(!feof(fp)) {
					MD5Update(&md5, encrypt, fread(encrypt, 1, sizeof(encrypt), fp));
				}
				fclose(fp);
			} while(0);
			
			MD5Final(&md5, decrypt);

			for(i=0; i<16; i++) {
				printf("%02x", decrypt[i]);  //02x前需要加上 %
			}
			
			printf("  %s\n", argv[n]);
		}
	} else {
		for(n=1; n<argc; n++) {
			MD5Init(&md5);
			MD5Update(&md5, argv[n], strlen(argv[n]));
			MD5Final(&md5, decrypt);

			for(i=0; i<16; i++) {
				printf("%02x", decrypt[i]);  //02x前需要加上 %
			}
			
			printf("  %s\n", argv[n]);
		}
	}

	return 0;
}  

