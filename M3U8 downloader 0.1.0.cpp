/*
DOS COMMAND LIST
	CLS
		clean screen
	bitsadmin /transfer myDownLoadJob /download /priority normal "http://192.168.203.140/b.ps1" "E:\\phpstudy_pro\\WWW\\b.ps1"
		download files
	
To make Meta-Class on Windows10 Browser convenient, I created this
program to download videos in .m3u8 format. -Kareno Akatsuki 20210809
*/
#include<ctime>
#include<cstring>
#include<iostream>
#include<windows.h>
#include<fstream>

using namespace std;

ifstream fin;
ofstream fout;

bool END = false;
string FN;	//.m3u8 file name
string AD;	//.m3u8 file address
string VN;	//.tc   video name
string LK;	//      link of video lib on network

void INIT(void) {
	//START SHOW
	cout << "-= M3U8 DOWNLOADER =-" << endl;
	cout << "VER: 0.1.0 BETA" << endl;
	cout << "BY KARENO_AKATSUKI 2021" << endl << endl;
	
	cout << "[INFO]Creating Lib..." << endl;
	system("md D:\\M3U8DownloaderVideo\\Videos");
	cout << "[INFO]Finished" << endl << endl;
	
	system("pause");
	system("cls");
	
	return;
}

void GET_LINK() {
	int LEN = AD.length() - 1;
	int RES = 0;
	for(int i = LEN; i >= 0; --i) {
		if(AD[i] == '/') {
			RES = i;
			break;
		}
	}
	for(int i = 0; i <= RES; ++i) {
		LK += AD[i];
	}
	
	cout << "[INFO]Getting LINK..." << endl;
	cout << "[INFO]LINK = " << LK << endl;
	cout << "[INFO]LINK got" << endl;
	
	return;
}

int main(void) {
	
	INIT();
	
	//MAIN
	while(!END) {
		
		//GET ADDRESS
		cout << "Please input the NETWORK ADDRESS of the '.m3u8' file." << endl;
		cout << "Such as 'https://www.example.com/example/example.m3u8'." << endl;
		cout << "ADDRESS    : ";
		cin >> AD;
		
		GET_LINK();
		
		//INIT
		
		fout.open("D:\\M3U8DownloaderVideo\\Download.bat");	//download
		fout << "bitsadmin /transfer myDownLoadJob /download /priority normal \"";
		fout << AD;
		fout << "\" \"D:\\M3U8DownloaderVideo\\VIDEOLIST.txt\"";
		fout.close();
		
		//DOWNLOAD M3U8 FILE
		cout << "[Info]Downloading M3U8 File...";
		system("D:\\M3U8DownloaderVideo\\Download.bat");
		cout << "[Info]Downloading Finished";
		
		//CREAT DOWNLOAD LIST
		fin.open("D:\\M3U8DownloaderVideo\\VIDEOLIST.txt");
		fout.open("D:\\M3U8DownloaderVideo\\VideoDownload.bat");
		
		string CONTENT;
		int NUM = 0;
		
		while(fin >> CONTENT) {
			if(CONTENT[0] != '#') {
				++NUM;
				string DLK = LK + CONTENT;
				
				cout << "[INFO]Getting DOWNLOAD LINK..." << endl;
				cout << "[INFO]DOWNLOAD LINK = " << DLK << endl;
				cout << "[INFO]DOWNLOAD LINK got" << endl;
				
				fout << "bitsadmin /transfer myDownLoadJob /download /priority normal \"";
				fout << DLK;
				fout << "\" \"D:\\M3U8DownloaderVideo\\Videos\\VIDEO";
				fout << NUM;
				fout << ".ts\"" << endl;
				
			}
		}
		
		fin.close();
		fout.close();
		
		//DOWNLOAD VIDEOS
		cout << "[INFO]Downloading Videos..." << endl;
		system("D:\\M3U8DownloaderVideo\\VideoDownload.bat");
		cout << "[INFO]Downloading Finished" << endl;
		
		//MIX VIDEOS
		fout.open("D:\\M3U8DownloaderVideo\\Videos\\Mix.bat");
		fout << "copy /b ";
		for(int i = 1; i < NUM; ++i) {
			fout << "D:\\M3U8DownloaderVideo\\Videos\\VIDEO" << i << ".ts+";
		}
		fout << "D:\\M3U8DownloaderVideo\\Videos\\VIDEO" << NUM << ".ts D:\\M3U8DownloaderVideo\\VIDEO.ts";
		fout.close();
		
		cout << "[INFO]Mixing VIDEOS..." << endl;
		system("D:\\M3U8DownloaderVideo\\Videos\\Mix.bat");
		cout << "[INFO]VIDEOS Mixed" << endl;
		
		//BACKUP
		system("cls");
		cout << "The VIDEO is ready for you in \'D:\\M3U8DownloaderVideo\' now." << endl;
		cout << "Please create a BACKUP of your video," << endl;
		cout << "or your video will be DELETED by the program later." << endl;
		char ANS;
		do {
			cout << "Have you ALREADY created a BACKUP? Y/N : ";
			cin >> ANS;
		} while(ANS != 'Y');
		
		//LOOP
		cout << "Download another video? " <<endl;
		cout << "Make sure you have already create a BACKUP of your videos." << endl;
		cout << "Another video? Y/N : ";
		
		cin >> ANS;
		
		system("cls");
		system("rd /s /q D:\\M3U8DownloaderVideo");
		
		if(ANS != 'Y') {
			break;
		}
		
	}
	
	system("pause");
	return 0;
}
