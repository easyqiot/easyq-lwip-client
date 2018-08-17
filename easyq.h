#include "string.h"
#include "stdlib.h"

#include "espressif/esp_common.h"
#include "FreeRTOS.h"
#include "task.h"

#include "lwip/api.h"
#include "lwip/ip_addr.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "lwip/err.h"

#include "easyq_config.h"


#define LWIP_TCPIP_CORE_LOCKING 1
#define LWIP_SOCKET 1

#ifndef EASYQ_HOST
#define EASYQ_HOST "192.168.1.2"
#endif

#ifndef EASYQ_PORT
#define EASYQ_PORT "1085"
#endif

#ifndef EASYQ_READ_BUFFER_SIZE
#define EASYQ_READ_BUFFER_SIZE 1024
#endif

#ifndef EASYQ_PULL_INTERVAL
#define EASYQ_PULL_INTERVAL 100
#endif

#ifndef EASYQ_LOGIN
#define EASYQ_LOGIN "easyq-client1"
#endif


typedef struct EQSession {
	char * id;
    int socket;
    bool ready;
    char * readbuffer;
} EQSession;

typedef struct Queue {
    const char * name;
    size_t len;
    void (*callback) (const char *);
} Queue;

err_t easyq_init(EQSession ** session);
void easyq_close(EQSession * session);

err_t easyq_read(EQSession * session, char ** line, size_t * len);
err_t easyq_write(EQSession * session, const char * line, size_t len);
err_t easyq_push(EQSession * session, Queue * queue, const char * msg, size_t len);
err_t easyq_pull(EQSession * session, Queue * queue);
err_t easyq_read_message(EQSession * s, char ** msg, char ** queue_name, size_t * len);

Queue * Queue_new(const char * name);

err_t easyq_loop(EQSession * session, Queue * queues[], size_t queues_count);

