#define IOC_TEST_MAGIC    'T'
#define IOC_TEST_START    _IOW(IOC_TEST_MAGIC, 0x10, unsigned long)
#define IOC_TEST_STOP     _IOW(IOC_TEST_MAGIC, 0x11, unsigned long)
#define IOC_TEST_SET_NAME _IOW(IOC_TEST_MAGIC, 0x12, unsigned long)
#define IOC_TEST_GET_NAME _IOR(IOC_TEST_MAGIC, 0x13, unsigned long)
#define MAX_NAME_SIZE (16)
#define DEV_NAME  "test_drv"
#define DEV_NAME_FULL "/dev/"DEV_NAME
