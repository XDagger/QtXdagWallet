The Dagger (XDAG) Qt Wallet

- Community site: https://xdag.io
- The Main net was launched January 5, 2018 at 22:45 GMT.

- Purpose

	The purpose of the project is making a light Xdag Wallet that 
	can cross platform(such as Linux,Windows,MacOs) easily£¬and in the
	near future this project will be ported on Arm Architecture so that
	mobile devices can use the Xdag Wallet¡£ 

Install and run (windows):
-----------------------

- Install dependencies:
	
	- visual studio 2015(2017):
		
		https://www.visualstudio.com/downloads/
		
		Notice:
		Remember choose the Visual C++ Componet
	
	- Windows SDK( windows software development kit ):
		
		https://docs.microsoft.com/zh-cn/windows-hardware/drivers/debugger/debugger-download-tools
		
		Notice:
		When you install the win debuger,you must choose the option "Debugging Tools for windows"£¬if your are a starter of 
		Windows SDK£¬all options are suggested to choose¡£
	
	- Qt5.7.1:
		
		http://iso.mirrors.ustc.edu.cn/qtproject/archive/qt/5.7/5.7.1/qt-opensource-windows-x86-msvc2015_64-5.7.1.exe
		
		Notice:
		Qt5.7.1 has been included Qt Creator 4.2.0

- Clone from the git repository:
        
		$ git clone https://github.com/amazingMan2017/QtXdagWallet.git

- Open Qt Creator 4.2.0 and Configure the project
		
		(1)Files --> Open Files Or Project
			Open the Qt project file in the relative path "qt\QtXdagWallet\QtXdagWallet.pro"

		(2) Configure the compiler and debugger
			Tools --> Options --> Build and Run£¬and make sure the following option is auto detected
			
			Kit:
				make sure the kit is Desktop Qt %{Qt:Version} MSVC2015_64bit
			
			Debugger:
				make sure the Windows Debug Tools in the Windows SDK is auto detected:
				my Windows Debug Tools is auto detected in the path "C:\Program Files (x86)\Windows Kits\10\Debuggers\x86\cdb.exe"
			
			Qt Version:
				make sure you qmake.exe path is auto detected
				my qt version is auto detected as "H:\Qt\Qt5.7.1\5.7\msvc2015_64\bin\qmake.exe";
			
			Compiler:
				make sure your compiler is microsoft visual C++ 14.0 or higher

		(3) Set the build dir
			(Project --> Build)
			Click the project button in the Qt Creator 4.2.0 and Configure the Build Options£¬DISABLE the Shadow Build
			
		(4) Copy your Xdag Wallet File (if you already have an Xdag Wallet Account JUST FOR DEVELOPMENT)
			copy your xdag wallet file for development to the  relative path "QtXdagWallet\qt\QtXdagWallet"

		(5) Right Click the Project "QtXdagWallet " and Run

- Detailed Technical tutorials With Pictures
	
	If you want to see the Technical tutorials with pictures you can view the document on this branch  "QtXdagWallet/doc/cn/Run Xdag With Qt5.7.1+VS2015.docx"

- Contact information ( amazingbill2017@gmail.com )
	
	If you have any question and suggest on this project you can send email to my GMail¡£
	
		
Maintainers:
---------------
Bill (Xdag Address: ABnr08l/kpFfvKLDBzv0+smQhbJo1RVy )
