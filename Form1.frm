VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "M3U8 Downloader v0.2.0-α0.1.0  枯野アカツキPresent"
   ClientHeight    =   3075
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   7650
   LinkTopic       =   "Form1"
   ScaleHeight     =   3075
   ScaleWidth      =   7650
   StartUpPosition =   3  '窗口缺省
   Begin VB.TextBox Video_Path 
      Height          =   270
      Left            =   1200
      TabIndex        =   2
      ToolTipText     =   "项目文件夹路径"
      Top             =   1440
      Width           =   2535
   End
   Begin VB.CommandButton Download_Start 
      Caption         =   "开始下载"
      Height          =   495
      Left            =   2280
      TabIndex        =   1
      Top             =   2160
      Width           =   1455
   End
   Begin VB.TextBox Download_Link 
      Height          =   270
      Left            =   1200
      ScrollBars      =   1  'Horizontal
      TabIndex        =   0
      ToolTipText     =   ".m3u8格式文件链接"
      Top             =   840
      Width           =   5295
   End
   Begin VB.Label Label1 
      Caption         =   "\\M3U8DownloaderVideo\\Videos"
      Height          =   255
      Left            =   3960
      TabIndex        =   3
      Top             =   1440
      Width           =   2655
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim MP As String    'MAIN  PATH
Dim VP As String    'VIDEO PATH
Dim AD As String    '.M3U8 ADDRESS
Dim VL As String    'VIDEO LINK
Dim L  As Integer

Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

Private Sub Form_Load() 'LOAD
    
    
    
End Sub

Public Function GETLEN()
    L = Len(AD)
    Dim i As Integer
    For i = L To 1 Step -1
        If Mid(AD, i, 1) = Chr(47) Then
            VL = Mid(AD, 1, i)
            Exit For
        End If
    Next i
End Function

Private Sub Download_Start_Click() 'PRESS DWONLOAD BUTTOM
    
    'INIT
    
    Set FS = CreateObject("Scripting.FileSystemObject")
    
    'READ DIR
    
    MP = Video_Path.Text + "\M3U8DownloaderVideo\"
    VP = Video_Path.Text + "\M3U8DownloaderVideo\Videos\"
    AD = Download_Link.Text
    Dim a As String
    a = GETLEN()
    
    
    
    'CREATE DIR
    
    Set CMDC = CreateObject("wscript.shell")
    CMDC.run "cmd /c d: && md " + VP
    
    'DOWNLOAD .M3U8 FIle
    
    CMDC.run "cmd /c d: && bitsadmin /transfer myDownLoadJob /download /priority normal " + Chr(34) + AD + Chr(34) + " " + Chr(34) + MP + "VIDEOLIST.txt" + Chr(34)
    
    Do Until FS.FileExists(MP + "VIDEOLIST.txt")
        Sleep 500
    Loop
    
    'GET DOWNLOAD LIST
    
    Set FILE = FS.OpenTextFile(MP + "VIDEOLIST.txt", 1)
    
    Dim NUM As Integer
    NUM = 0
    
    Do Until FILE.AtEndOfStream
        Dim STR As String
        STR = FILE.ReadLine
        If Left(STR, 1) <> Chr(35) Then
            NUM = NUM + 1
            CMDC.run "cmd /c d: && bitsadmin /transfer myDownLoadJob /download /priority normal " + Chr(34) + VL + STR + Chr(34) + " " + Chr(34) + VP + "VIDEO" + CStr(NUM) + ".ts" + Chr(34)
            If NUM Mod 50 = 0 Then
                Do Until FS.FileExists(VP + "VIDEO" + CStr(NUM) + ".ts")
                    Sleep 500
                Loop
            End If
        End If
        
    Loop
    FILE.Close
    Do Until FS.FileExists(VP + "VIDEO" + CStr(NUM) + ".ts")
        Sleep 500
    Loop
    Dim i As Integer
    
    Dim COMMAND As String
    COMMAND = "cmd /c d: && copy /b "
        
    For i = 1 To NUM - 1
        COMMAND = COMMAND + VP + "VIDEO" + CStr(i) + ".ts+"
    Next i
        
    COMMAND = COMMAND + VP + "VIDEO" + CStr(NUM) + ".ts " + MP + "VIDEO.ts"
        
    CMDC.run COMMAND
    
    MsgBox "下载完成"
End Sub
