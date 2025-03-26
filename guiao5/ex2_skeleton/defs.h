
#define RESPONSE_FIFO "../fifos/response_fifo"
#define REQUEST_FIFO "../fifos/request_fifo"
#define BUFF_SIZE 2048

typedef struct msg{
    int needle;
    int pid;
    int occurrences;
} Msg;