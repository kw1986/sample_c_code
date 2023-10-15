#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "linked_list.h"

#define NEWLINE_CHARACTER	0x0a
#define WHITESPACE	0x20

LinkedList* split_data_by_whitespace(const char* line) {
	
	LinkedList* line_record = NULL;
	char* data = NULL;
	int start_pos = 0;
	int end_pos = 0;
	int len = 0;
	bool is_skip_whitespace = false;

	if(!line) {
		return NULL;
	}
	
//	for(int x=0; x < strlen(line); x++) {
//		printf("char[%c], position[%d]\n", line[x], x);
//	}
	
	line_record = linked_list_create();
	
	for(int i = 0; i < strlen(line); i++) {
		
		end_pos++;
		
		if((line[i] == WHITESPACE) && (is_skip_whitespace == false)) {				
			len = end_pos - start_pos -1;
			
			data = (char*)malloc(len + 1);
			//printf("copy at position[%d], length[%d]", start_pos, len);
			memcpy(data, &line[start_pos], len);
			data[len + 1] = '\0';
			linked_list_append(line_record, data);
			//printf("%s\n", data);
			start_pos = end_pos;
			is_skip_whitespace = true;

		}
		else if ((line[i] != WHITESPACE) && (is_skip_whitespace == true)) {
			is_skip_whitespace = false;
			start_pos = i;
			end_pos = i + 1;
			//printf(">>>start_pos=%d, end_pos=%d\n", start_pos, end_pos);
		}

		
	}
	//printf(">>>start_pos=%d, end_pos=%d\n", start_pos, end_pos);
	if((strlen(line) > 0) && (is_skip_whitespace == false)) {
		if((start_pos == 0) && (end_pos == 0)) {
			len = strlen(line);
			data = (char*)malloc(len + 1);
			memcpy(data, &line[start_pos], len);
			data[len + 1] = '\0';
			linked_list_append(line_record, data);
			//printf("%s\n", data);
			
		}
		else {
			len = end_pos - start_pos;			
			data = (char*)malloc(len + 1);
			memcpy(data, &line[start_pos], len);
			data[len + 1] = '\0';
			linked_list_append(line_record, data);
			//printf("%s\n", data);			
		}
	}

	
	return line_record;
}

/* Read record line by line and store it into linked-list structure */
LinkedList* read_record(const char* filename) {
	FILE *fp;

	char buffer[1];
	char line_buffer[2000];
	int start_pos = 0;
	int end_pos = 0;
	int prev_fp_offset = 0;
	int fp_length = 0;
	int pos = 0;
	LinkedList* line_record = NULL;
	LinkedList* line_records = NULL;

   fp = fopen(filename,"r");
   if(fp == NULL) 
   {
      perror("Error in opening file");
      return NULL;
   }
	
	line_records = linked_list_create();
	
	/* Make sure it point to the beginning of file */
	fseek(fp, 0, SEEK_SET);

   /* Read line by line and store it into struct (linked-list) */
   while (fread(buffer, 1, 1, fp) != false) {
		start_pos++;
		
		//printf("pos[%d], char=%c, %x\n", start_pos, buffer[0], buffer[0]);
		
		/* Newline handling */
		if(buffer[0] == NEWLINE_CHARACTER) {
			end_pos = start_pos - 1;
			fp_length = end_pos - prev_fp_offset;

			//printf("fseek pos=%d, fread length=%d\n", prev_fp_offset, fp_length);
			
			fseek(fp, prev_fp_offset, SEEK_SET);
			
			fread(line_buffer, 1, fp_length, fp);
			
			char* line = NULL;
			line = (char*)malloc(fp_length + 1);
			memcpy(line, line_buffer, fp_length);
			line[fp_length + 1] = '\0';
			
			/* Split data by whitespace from this line */
			line_record = split_data_by_whitespace(line);
			
			linked_list_append(line_records, line_record);
			
			/* I have line record here */
		    //printf("%s\n",line);
			free(line);
			
			/* Remember to reset everything here */
			memset(line_buffer, '\0', sizeof(line_buffer));
			fseek(fp, start_pos, SEEK_SET);
			
			/* Update the previous offset to current offset */
			prev_fp_offset = start_pos;

		}	
   }
   
   fclose(fp);
   
   return line_records;
}

void show_record(LinkedList* records) {
	
	LinkedList* record = NULL;
	char* data = NULL;
	
	if(!records) {
		return;
	}
	
	for(int line = 0; line < linked_list_len(records) ; line++) {
		 record = (LinkedList*)linked_list_get(records, line);
		 
		 for(int pos = 0; pos < linked_list_len(record); pos++) {
			 data = (char*)linked_list_get(record, pos);
			 printf("line[%d] data[%d]: %s\n", line+1, pos+1, data);
		 }	 
	}

	return;
}

void change_record(LinkedList* records, const char* from_str, const char* to_str) {
	
	LinkedList* record = NULL;
	char* data = NULL;
	int start_pos = 0;
	int end_pos = 0;

	bool is_first_match_char = false;
	bool is_matched = false;
	int len = 0;
	
	for(int line = 0; line < linked_list_len(records) ; line++) {
		 record = (LinkedList*)linked_list_get(records, line);
		 
		 for(int pos = 0; pos < linked_list_len(record); pos++) {
			 data = (char*)linked_list_get(record, pos);
			 
			 is_matched = false;
			 is_first_match_char =false;
			 start_pos = 0;
			 
			 for(int i = 0, n = 0; i < strlen(data); i++) {
				 if(data[i] == from_str[i]) {
					//printf("data=%c, str=%c\n", data[i], from_str[i]);
					 if(is_first_match_char == false) {
						start_pos = i;
						is_first_match_char = true;	 
					 }
						
					if(++n == strlen(from_str)) {
						/* Got matched */
						is_matched = true;
						len = n;
						break;
					}	
				 }
				 else {
					 n = 0;
					 is_first_match_char = false;
				 }
			 }
			 
			 if(is_matched) {
				 /* change the data here */
				 //printf("Match position[%d], len=%d\n", start_pos, len);

				 if(strlen(to_str) > len) {
					 /* Reallocate memory is required here */
					 data = (char*)realloc(data, sizeof(data) + strlen(to_str) - len);
					 memmove(&data[start_pos + strlen(to_str)],&data[len],20);
					 memcpy(&data[start_pos], &to_str[0], strlen(to_str));
					 //printf("memmove dest %d, src %d\n", strlen(to_str), len);
					 //printf("After change data = %s\n", data);
				 }
				 else {
					 //TODO: Don't hardcode like '20' for below memory moved.
					 memmove(&data[start_pos + strlen(to_str)],&data[len],20);
					 memcpy(&data[start_pos], &to_str[0], strlen(to_str));
					 //printf("memmove dest %d, src %d", len-strlen(to_str), len);
					 //printf("After change data = %s\n", data);
				 }
			 }
	 
		 }	 
	}	
}

void write_record(LinkedList* records, const char* filename) {
	
	FILE * fp;
	LinkedList* record = NULL;
	char* data = NULL;
	char whitespace[4] = "   ";
	char newline = '\n';
	
	fp = fopen (filename, "w");
   
	for(int line = 0; line < linked_list_len(records) ; line++) {
		 record = (LinkedList*)linked_list_get(records, line);
		 
		 for(int pos = 0; pos < linked_list_len(record); pos++) {
			 data = (char*)linked_list_get(record, pos);
			 
			 fwrite(data , 1 , strlen(data) , fp);
			 
			 if(pos != linked_list_len(record) - 1) {
				 fwrite(whitespace , 1 , strlen(whitespace) , fp);
			 } 
        }
		 
		if(line != linked_list_len(records) - 1) {
			fwrite(&newline , 1 , 1 , fp);
		}
		 
	}

   fclose(fp);
}

int main() {
	
	/* Data structure to store all records from the file */
	LinkedList* file_data = NULL; 
	
	if((file_data = read_record("ASCII_DATA.txt")) != NULL) {
		
        show_record(file_data);
        
		change_record(file_data, "DATA", "MYDATA");

		/*Write the record to output file */
		write_record(file_data, "output.txt");
	}

	/* should have memory leak in the program, ignore it first. */

	return 0;
}