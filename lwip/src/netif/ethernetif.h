#define        BaseAddr         0x06000000

#define       REGISTERADDR(x)   (BaseAddr+x)

#define        rRWPORT          REGISTERADDR(10)         //��д��ַ

#define        rRESETPORT       REGISTERADDR(18)         //��λ��ַ

/* Page 0 */
//Page0�Ŀ�д�Ĵ���

#define        rCR                 REGISTERADDR(0)  //CR�Ĵ���

#define        rPSTART             REGISTERADDR(1)  //��ʼҳ��Ĵ���

#define        rPSTOP              REGISTERADDR(2)  //ֹͣҳ��Ĵ���

#define        rBNRY               REGISTERADDR(3)  //�߽�Ĵ���

#define        rTPSR               REGISTERADDR(4)  //����ҳ��ʼ�Ĵ���

#define        rTBCR0              REGISTERADDR(5)  //�����ֽڼ�������������λ��

#define        rTBCR1              REGISTERADDR(6)  //�����ֽڼ�������������λ��

#define        rISR                REGISTERADDR(7)  //�ж�״̬�Ĵ���

#define        rRSAR0              REGISTERADDR(8)  //Զ��DMA��ַ�Ĵ�������λ��

#define        rRSAR1              REGISTERADDR(9)  //Զ��DMA��ַ�Ĵ�������λ��

#define        rRBCR0              REGISTERADDR(10)         //Զ��DMA�ֽڼ����Ĵ�������λ��

#define        rRBCR1              REGISTERADDR(11)         //Զ��DMA�ֽڼ����Ĵ�������λ��

#define        rRCR                REGISTERADDR(12)         //�������üĴ���

#define        rTCR                REGISTERADDR(13)         //�������üĴ���

#define        rDCR                REGISTERADDR(14)         //�������üĴ���

#define        rIMR                REGISTERADDR(8)  //�ж����μĴ���

//Page0��ֻ���Ĵ�������Ӧ�����ļĴ���

#define       rCLDA0             REGISTERADDR(1)  //����DMA��ַ����λ��

#define        rCLDA1            REGISTERADDR(2)  //����DMA��ַ����λ��

#define       rTSR               REGISTERADDR(4)  //����״̬�Ĵ���

#define       rNCR               REGISTERADDR(5)  //��ײ�����Ĵ���

#define       rFIFO              REGISTERADDR(6)  //FIFO

#define       rCRDA0             REGISTERADDR(8)  //Զ��DMA��ַ����λ��

#define       rCRDA1             REGISTERADDR(9)  //Զ��DMA��ַ����λ��

#define       r8019ID0           REGISTERADDR(10)         //8019ID�Ĵ�������λ��

#define       r8019ID1           REGISTERADDR(11)         //8019ID�Ĵ�������λ��

#define        rRSR              REGISTERADDR(12)         //����״̬�Ĵ���

#define        rCNTR0            REGISTERADDR(13)         //���ն������Ĵ���

#define       rCNTR1             REGISTERADDR(14)         //����CRC���������

#define       rCNTR2             REGISTERADDR(8)  //���ն�ʧ֡����Ĵ���

/* Page 1 */

#define        rPAR0                 REGISTERADDR(1)  //�����ַ�Ĵ���

#define        rPAR1                 REGISTERADDR(2)

#define        rPAR2                 REGISTERADDR(3)

#define        rPAR3                 REGISTERADDR(4)

#define        rPAR4                 REGISTERADDR(5)

#define        rPAR5                 REGISTERADDR(6)

#define        rCURR                REGISTERADDR(7)  //��ǰҳ��Ĵ���

#define        rMAR0               REGISTERADDR(8)  //�ಥ��ַ�Ĵ���

#define        rMAR1               REGISTERADDR(9)

#define        rMAR2               REGISTERADDR(10)

#define        rMAR3               REGISTERADDR(11)

#define        rMAR4               REGISTERADDR(12)

#define        rMAR5               REGISTERADDR(13)

#define        rMAR6               REGISTERADDR(14)

#define        rMAR7               REGISTERADDR(8)

/*Page2�����мĴ�����ֻ��*/

#define        rPSTART             REGISTERADDR(1)

#define        rPSTOP              REGISTERADDR(2)

#define        rTPSR               REGISTERADDR(4)

#define        rRCR                REGISTERADDR(12)

#define        rTCR                REGISTERADDR(13)

#define        rDCR                REGISTERADDR(14)

#define        rIMR                REGISTERADDR(8)

/* Page 3 */
#define        rCR9346             REGISTERADDR(1)
#define        rCONFIG0            REGISTERADDR(3)
#define        rCONFIG1            REGISTERADDR(4)
#define        rCONFIG2            REGISTERADDR(5)
#define        rCONFIG3            REGISTERADDR(6)