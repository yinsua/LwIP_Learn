#include "lwip/netif.h"
#include "lwip/ip.h"
#include "lwip/tcp.h"
#include "lwip/init.h"
#include "netif/etharp.h"
#include "lwip/timers.h"

//extern functions
extern err_t ethernetif_init(struct netif *netif);
extern void process_mac(void);

//global data
struct netif enc28j60_netif;

void lwip_init_task(void)
{
	struct ip_addr ipaddr, netmask, gw;

  lwip_init();
	IP4_ADDR(&gw, 169,254,11,1);
	IP4_ADDR(&ipaddr, 169,254,11,4);
	IP4_ADDR(&netmask, 255,255,0,0);

  netif_add(&enc28j60_netif, &ipaddr, &netmask, &gw, NULL, ethernetif_init,ethernet_input);
	netif_set_default(&enc28j60_netif);
	netif_set_up(&enc28j60_netif);
	
}

void tcpserver_init(void);

void lwip_demo(void *pdata)
{
	//init LwIP
	lwip_init_task();
 	
	//init a tcp server
 	tcpserver_init();

	//for periodic handle
	while(1)
	{
		//process_mac();
		
		//process LwIP timeout
		sys_check_timeouts();
		
		//todo: add your own user code here

	}
}

void tcp_send_pbuf_data_out(struct tcp_pcb *pcb, struct pbuf *p)
{
	if (NULL == pcb || NULL == p)
	{
	    return;
	}
		
	while(p != NULL)
	{
		tcp_write(pcb, p->payload, p->len, 0);
		p = p->next;
	}
}

static err_t http_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{

  //  char *rq;

  /* We perform here any necessary processing on the pbuf */
  if (p != NULL) 
  {        
	/* We call this function to tell the LwIp that we have processed the data */
	/* This lets the stack advertise a larger window, so more data can be received*/
	tcp_recved(pcb, p->tot_len);

     {
      // Uart_Printf("Do tcp write when receive\n");
       //tcp_write(pcb, p->payload, p->len, 0);
	   tcp_send_pbuf_data_out(pcb,p);
	   //tcp_write(pcb, p->payload, p->len, 0);
     }
     pbuf_free(p);
    } 
  else if (err == ERR_OK) 
  {
    /* When the pbuf is NULL and the err is ERR_OK, the remote end is closing the connection. */
    /* We free the allocated memory and we close the connection */
    return tcp_close(pcb);
  }
  return ERR_OK;
}

/**
  * @brief  This function when the Telnet connection is established
  * @param  arg  user supplied argument 
  * @param  pcb	 the tcp_pcb which accepted the connection
  * @param  err	 error value
  * @retval ERR_OK
  */

static err_t http_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{     
  
  /* Tell LwIP to associate this structure with this connection. */
 // tcp_arg(pcb, mem_calloc(sizeof(struct name), 1));	
  
  /* Configure LwIP to use our call back functions. */
 // tcp_err(pcb, HelloWorld_conn_err);
 // tcp_setprio(pcb, TCP_PRIO_MIN);
  tcp_recv(pcb, http_recv);
 // tcp_poll(pcb, http_poll, 10);
 //  tcp_sent(pcb, http_sent);
  /* Send out the first message */  
 // tcp_write(pcb, GREETING, strlen(GREETING), 1); 
  return ERR_OK;
}

/**
  * @brief  Initialize the hello application  
  * @param  None 
  * @retval None 
  */
 
void tcpserver_init(void)
{
  struct tcp_pcb *pcb;	            		
  
  /* Create a new TCP control block  */
  pcb = tcp_new();	                		 	

  /* Assign to the new pcb a local IP address and a port number */
  /* Using IP_ADDR_ANY allow the pcb to be used by any local interface */
  tcp_bind(pcb, IP_ADDR_ANY, 6060);       


  /* Set the connection to the LISTEN state */
  pcb = tcp_listen(pcb);				

  /* Specify the function to be called when a connection is established */	
  tcp_accept(pcb, http_accept);   
										
}
