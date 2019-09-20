#include <iostream>
#include<winsock.h>
#include <thread>
#include "timer.h"
#include "gtest/gtest.h"

//定义程序中使用的常量      
#define SERVER_ADDRESS "127.0.0.1" //服务器端IP地址      
#define PORT           5150         //服务器的端口号      
#define MSGSIZE        4096         //收发缓冲区的大小      
#pragma comment(lib, "ws2_32.lib")  
#include "CSerialPort.h"
#include "serial_send_data.h"



int pipeserver()
{
	srand(time(NULL));

	char buf[256] = "";
	DWORD rlen = 0;
	HANDLE hPipe = CreateNamedPipe(
		TEXT("\\\\.\\Pipe\\mypipe"),                        //管道名  
		PIPE_ACCESS_DUPLEX,                                 //管道类型   
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  //管道参数  
		PIPE_UNLIMITED_INSTANCES,                           //管道能创建的最大实例数量  
		0,                                                  //输出缓冲区长度 0表示默认  
		0,                                                  //输入缓冲区长度 0表示默认  
		NMPWAIT_WAIT_FOREVER,                               //超时时间  
		NULL);                                                  //指定一个SECURITY_ATTRIBUTES结构,或者传递零值.  
	if (INVALID_HANDLE_VALUE == hPipe)
	{
		printf("Create Pipe Error(%d)\n", GetLastError());
	}
	else
	{
		printf("Waiting For Client Connection...\n");
		if (ConnectNamedPipe(hPipe, NULL) == NULL) //阻塞等待客户端连接。  
		{
			printf("Connection failed!\n");
		}
		else
		{
			printf("Connection Success!\n");
		}

		while (true)
		{
			if (ReadFile(hPipe, buf, 256, &rlen, NULL) == FALSE) //接受客户端发送过来的内容  
			{
				printf("Read Data From Pipe Failed!\n");
				break;
			}
			else
			{
				printf("From Client: data = %s, size = %d\n", buf, rlen);
				char wbuf[256] = "send message to CLIENT id:";
				sprintf(wbuf, "%s%d", wbuf, rand() % 1000);
				DWORD wlen = 0;
				WriteFile(hPipe, wbuf, sizeof(wbuf), &wlen, 0); //向客户端发送内容  
				printf("To Client: data = %s, size = %d\n", wbuf, wlen);
				Sleep(1000);
			}
		}
		CloseHandle(hPipe);//关闭管道  
	}

	system("PAUSE");
	return 0;
}

TEST(PIPE_SERVER,Normal)
{
	TimeTrack ab;

	ab.Track();
	pipeserver();
}



//TimeTrack track;
void initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;

	err = WSAStartup(w_req, &wsadata);
	if (err != 0) 
	{
		cout << "初始化套接字库失败！" << endl;
	}
	else 
	{
		cout << "初始化套接字库成功！" << endl;
	}

	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else 
	{
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息
}

int socket_server(char *msg,const int msg_len)
{
	//这个结构被用来存储 被WSAStartup函数调用后返回的 Windows Sockets数据
	WSADATA wsaData;

	//连接所用套节字    
	SOCKET sClient;

	//保存远程服务器的地址信息      
	SOCKADDR_IN server;

	//收发缓冲区      
	//char szMessage[MSGSIZE];

	//成功接收字节的个数      
	int ret;

	// Initialize Windows socket library      
	WSAStartup(0x0202, &wsaData);

	// 创建客户端套节字      
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INET指明使用TCP/IP协议族；      
														 //SOCK_STREAM, IPPROTO_TCP具体指明使用TCP协议      
	// 指明远程服务器的地址信息(端口号、IP地址等)      
	memset(&server, 0, sizeof(SOCKADDR_IN)); //先将保存地址的server置为全0

	server.sin_family = PF_INET; //声明地址格式是TCP/IP地址格式      
	server.sin_port = htons(PORT); //指明连接服务器的端口号，htons()用于 converts values between the host and network byte order      
	server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS); //指明连接服务器的IP地址      
														//结构SOCKADDR_IN的sin_addr字段用于保存IP地址，sin_addr字段也是一个结构体，sin_addr.s_addr用于最终保存IP地址      
														//inet_addr()用于将 形如的"127.0.0.1"字符串转换为IP地址格式      
	//连到刚才指明的服务器上      
	connect(sClient, (struct sockaddr *) &server, sizeof(SOCKADDR_IN)); //连接后可以用sClient来使用这个连接      
																		//server保存了远程服务器的地址信息      
	while (TRUE) {
		cout << "Send:" << msg << endl;
		//从键盘输入      
		// 发送数据      
		send(sClient, msg, msg_len, 0); //sClient指明用哪个连接发送； szMessage指明待发送数据的保存地址 ；strlen(szMessage)指明数据长度      
	}

	// 释放连接和进行结束工作      
	closesocket(sClient);
	WSACleanup();
}


TEST(Socket_Send, Normal_char)
{
	char msg[] = "hello world";
	initialization();
	socket_server(msg,sizeof(msg));

	cout << "finish socket" << endl;
}



TEST(TEST_ST_HZ,Normal)
{
	//int t1 = track.Track();
	CSerialPort mySerialPort;
	if (!mySerialPort.InitPort(17, 460800))
	{
		std::cout << "initPort fail !" << std::endl;
	}
	else
	{
		std::cout << "initPort success !" << std::endl;
	}

	this_thread::sleep_for(1s);
	//int t2 = track.Track();
	//cout << track.DurationTime(t1, t2) / 1000000.0 << " seconds" << endl;

	//char *buf = new char[10240];
	//int buflen = 0;

	mySerialPort.OpenListenThread();
	std::this_thread::sleep_for(1s);
	mySerialPort.CloseListenTread();
}


TEST(CSERIAL_PORT,SEND)
{
	CSerialPort mySerialPort;
	if (!mySerialPort.InitPort(7, CBR_115200))
	{
		std::cout << "initPort fail !" << std::endl;
	}
	else
	{
		std::cout << "initPort success !" << std::endl;
	}

	unsigned char buf[8][kmaxbuflen];
	unsigned char buf1[kmaxbuflen];

	//int len = GenerateDop(buf);
	//int len = GenerateBestpos(buf);
	//int len = GenerateBestsats(buf);
	//int len = GenerateSatvis2(buf);
	//int len = GenerateTrackstat(buf);
	novatel nov_data;
	int all_len[8]{0};
	int len = 0;
	int sys_nov;
	GetNovetal_data(nov_data);

	nov_data.msg_id = 42;
	nov_data.msg_len = 72;
	len = ConstructBestPos(buf1, &nov_data, len);
	//all_len[1] = ConstructBestPos(buf[1], &nov_data, all_len[1]);


	nov_data.msg_id = 174;
	nov_data.msg_len = 28 + nov_data.nSVs * 4;
	len = ConstructDop(buf1, &nov_data, len);
	//all_len[0] = ConstructDop(buf[0], &nov_data, all_len[0]);


	nov_data.msg_id = 1194;
	nov_data.msg_len = 4 + nov_data.nSVs * 16;
	len = ConstructBestSats(buf1, &nov_data, len);
	//all_len[2] = ConstructBestSats(buf[2], &nov_data, all_len[2]);

	nov_data.msg_id = 1043;

	for (int sys = 0 ; sys < 4 ; sys++)
	{
		nov_data.msg_len = 16 + nov_data.satnum[sys] * 40;
		len = ConstructSatVis2(buf1, &nov_data, len, sys);
		//all_len[sys + 3] = ConstructSatVis2(buf[sys + 3], &nov_data, all_len[sys + 3], sys);
	}

	nov_data.msg_id = 83;
	nov_data.msg_len = 16 + nov_data.nSVs * 80;
	len = ConstructTraceBack(buf1, &nov_data, len);
	//all_len[7] = ConstructTraceBack(buf[7], &nov_data, all_len[7]);




	while(true)
    {
		for (int i = 0 ; i < 8 ; i++)
		{
			//if (!mySerialPort.WriteData((char*)buf[i], all_len[i] / 8))
			if (!mySerialPort.WriteData((char*)buf1, len / 8))
			{
				std::cout << "Send Data Failed!" << std::endl;
			}
			else
				std::cout << "Send Data success!" << std::endl;
			Sleep(100);
		}
    }
    
}


void finish()
{
	int len = 0,sys;
	novatel nov_data;
	unsigned char buf[kmaxbuflen];

	nov_data.msg_id = 42;
	nov_data.msg_len = 72;
	len = ConstructBestPos(buf, &nov_data, len);


	nov_data.msg_id = 174;
	nov_data.msg_len = 28 + nov_data.nSVs * 4;
	len = ConstructDop(buf, &nov_data, len);


	nov_data.msg_id = 1194;
	nov_data.msg_len = 4 + nov_data.nSVs * 16;
	len = ConstructBestSats(buf, &nov_data, len);

	nov_data.msg_id = 1043;
	for (sys = 0; sys < 4; sys++)
	{
		nov_data.msg_len = 16 + nov_data.satnum[sys] * 40;
		len = ConstructSatVis2(buf, &nov_data, len, sys);
	}

	nov_data.msg_id = 83;
	nov_data.msg_len = 16 + nov_data.nSVs * 80;
	len = ConstructTraceBack(buf, &nov_data, len);

}


//if (!mySerialPort.OpenListenThread())
//{
//	std::cout << "OpenListenThread fail !" << std::endl;
//}
//else
//{
//	std::cout << "OpenListenThread success !" << std::endl;
//}
//
//int temp;
//std::cin >> temp;

