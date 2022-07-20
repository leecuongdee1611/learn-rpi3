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

mqd_t mqd;
pthread_t thread1_id, thread2_id;
bool import_data = false;
struct info
{
	char name[50];
	char phone[20];
	char age[5];
	char img[30];
};
int print_img(char name_img[20]);
int check_phone(char phone[20]);
static void *thread_1(void *argv);
static void *thread_2(void *argv);

int main(void) {
	struct mq_attr attr;
		attr.mq_flags = 0;
		attr.mq_maxmsg = 10;
		attr.mq_msgsize = sizeof(struct info);
		attr.mq_curmsgs = 0;
	mqd = mq_open("/My_queue", O_RDWR , 0600, &attr);
	if(mqd == -1)
	{
		mqd = mq_open("/My_queue", O_CREAT | O_EXCL | O_RDWR, 0600, &attr);
	}
		
	pthread_create(&thread1_id, NULL, &thread_1, NULL);	
	pthread_create(&thread2_id, NULL, &thread_2, NULL);	
	
	pthread_join(thread1_id, NULL);
	pthread_join(thread2_id, NULL);
	return 0;
}


static void *thread_1(void *argv) {
	struct info info_input;
	
	while(1){
		while(!import_data){
		
			printf("Nhap vao ho va ten:\n");
			fgets(info_input.name, sizeof(info_input.name), stdin);
			printf("Nhap vao so dien thoai:\n");
			fgets(info_input.phone, sizeof(info_input.phone), stdin);
			printf("Nhap vao tuoi:\n");
			fgets(info_input.age, sizeof(info_input.age), stdin);
			printf("Nhap vao ten anh:\n");
			fgets(info_input.img, sizeof(info_input.img), stdin);
		if(mq_send(mqd, (char *)&info_input, sizeof(info_input),0) == -1)
			printf("Failed to send data");
		else import_data = true;
			

		}	
	}
}



static void *thread_2(void *argv) {
	struct info info_output;

	while(1) {
		if(mq_receive(mqd, (char *)&info_output, sizeof(struct info), 0) == -1)
			printf("Failed to recive data\n");
		else if(check_phone(info_output.phone) == 0) {
			printf("Ho va ten: %s\n", info_output.name);
			printf("So dien thoai: %s\n", info_output.phone);
			printf("Tuoi: %s\n", info_output.age);
			info_output.img[strlen(info_output.img)-1] = '\0';
			printf("Ten anh: %s\n", info_output.img);
			print_img(info_output.img);
			import_data = false;
		}
		else {
			printf("Wrong format\n");
			import_data = false;
		} 
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


