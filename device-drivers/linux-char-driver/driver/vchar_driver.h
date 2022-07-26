#define REG_SIZE 1 //kich thuoc 1 thanh ghi laf 1 byte
#define NUM_CTRL_REGS 1 // so thanh ghi dieu khien cua thiet bi
#define NUM_STS_REGS 5 // so thanh ghi trang thai cua thiet bi
#define NUM_DATA_REGS 256 // so thanh ghi du lieu cua thiet bi
#define NUM_DEV_REGS (NUM_CTRL_REGS + NUM_STS_REGS + NUM_DATA_REGS) //tong so thanh ghi cua thiet bi


/*MO TA CAC THANH GHI TRNAG THAI*/

// moi lan doc thanh cong tu cac thanh ghi du lieu, tang len 1 don vi
#define READ_COUNT_H_REG 0
#define READ_COUNT_L_REG 1

// moi lan ghi thanh cong vao cac thanh ghi du lieu, tang them 1 don vi
#define WRITE_COUNT_H_REG 2
#define WRITE_COUNT_L_REG 3

/* DEVICE_STATUS_REG:
	-gia tri khoi tao: 0x03
	- 0: khong san sang, 1: san sang
	- bit 0: de doc. bit 1: de ghi.
	- bit 2: 0 khi cac thanh ghi du lieu bi xoa, 1 khi toan bo cac thanh ghi du lieu da bi ghi
*/
#define DEVICE_STATUS_REG 4

#define STS_READ_ACCESS_BIT (1<<0)
#define STS_WRITE_ACCESS_BIT (1<<1)
#define STS_DATAREGS_OVERFLOW_BIT (1<<2)

#define READY 1
#define NOT_READY 0
#define OVERFLOW 1
#define NOT_OVERFLOW 0


/*MO TA CAC THANH GHI DIEU KHIEN*/
/*CONTROL_ACCESS_REG: chua cac bit dieu khien kha nang doc/ghi cac thanh ghi du lieu. khoiw tao 0x03
	bit0: 0 khong cho phep doc. 1 cho phep doc
	bit1: 0 khong cho phep ghi. 1 cho phep ghi
*/	
#define CONTROL_ACCESS_REG 0

#define CTRL_READ_DATA_BIT (1 << 0)
#define CTRL_WRITE_DATA_BIT (1 << 1)

#define ENABLE 1
#define DISABLE 0
