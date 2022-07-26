#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdbool.h>


#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

bool import_data = false;
pthread_t thread1_id, thread2_id;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct info
{
	char name[50];
	char phone[20];
	char age[5];
	char img[30];
}user_info;

int print_img(char name_img[20]);
int check_phone(char phone[20]);
static void *thread_1(void *argv);
static void *thread_2(void *argv);

int main(void) {

	pthread_create(&thread1_id, NULL, &thread_1, NULL);
	pthread_create(&thread2_id, NULL, &thread_2, NULL);
	
	pthread_join(thread1_id, NULL);
	pthread_join(thread2_id, NULL);
	return 0;
}


static void *thread_1(void *argv) {
while(1)
{
	pthread_mutex_lock (&mutex);
	while(!import_data){
	
		pthread_cond_wait(&cond,&mutex);
	
		printf("Nhap vao ho va ten:\n");
		fgets(user_info.name, sizeof(user_info.name), stdin);
		printf("Nhap vao so dien thoai:\n");
		fgets(user_info.phone, sizeof(user_info.phone), stdin);
		printf("Nhap vao tuoi:\n");
		fgets(user_info.age, sizeof(user_info.age), stdin);
		printf("Nhap vao ten anh:\n");
		fgets(user_info.img, sizeof(user_info.img), stdin);
		import_data = true;
	}
	pthread_mutex_unlock (&mutex);
}
}



static void *thread_2(void *argv) {
while(1)
{
	pthread_mutex_lock (&mutex);
	while(import_data) {
		if(check_phone(user_info.phone) == 0) {
			printf("Ho va ten: %s\n", user_info.name);
			printf("So dien thoai: %s\n", user_info.phone);
			printf("Tuoi: %s\n", user_info.age);
			user_info.img[strlen(user_info.img)-1] = '\0';
			printf("Ten anh: %s\n", user_info.img);
			print_img(user_info.img);
		}
		else {
			printf("Wrong format\n");
		}
	import_data =false;
	}
	pthread_mutex_unlock (&mutex);
	pthread_cond_signal(&cond);
}
}



int check_phone(char phone[20]) {
	if(strlen(phone) !=11)
		return -1;
	if(phone[0] !='0')
		return -1;
	
	switch(phone[1])
	{
		case '9':
			if(phone[2] == '5') return -1;
			else return 0;
		break;
		
		case '8':
			if(phone[2] == '0' | phone[2] == '7') return -1;
			else return 0;
		break;
		
		case '7':
			if(phone[2] == '1' | phone[2] == '2' | phone[2] == '3' | phone[2] == '4' | phone[2] == '5') return -1;
			else return 0;
		break;
		
		case '5':
			if(phone[2] == '6' | phone[2] == '8') return 0;
			else return -1;
		break;
		
		case '3':
			if(phone[2] == '0' | phone[2] == '1') return -1;
			else return 0;
		
		break;
		
		default: 
			return -1;
	
	
	
	
	}
}


int print_img(char name_img[20])
{
	FILE* fp = NULL;
	size_t size;
	unsigned char *val;

	fp = fopen(name_img,"rb");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	val = (char *)malloc(size);
	
	if(fp == NULL) printf("Failed\n");
	else 
	{
		printf("Successed\n");
		fread(val, size, 1,fp);
		for(int i=0; i<16; i++)
		{
			printf("%02x ",val[i]);
		}
		printf("\n");
	}
	fclose(fp);
	free(val);
	return 0;
}
