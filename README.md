MFC 기반 MES 클라이언트 시뮬레이션 구현
가상 I/O 이벤트, MES 이벤트 처리 예시

장비 UI 개발 담당 당시의 주요 업무를 재현한 내용이다.

빌드 환경: MesClientExample/MesClientExample.sln
Visual Studio 2022
x64 Debug/Release 

주요 파일
MesClientExample/MesClientExample/MainFrm.cpp: 메시지 라우팅(WM_IO_EVENT, WM_MES_REPLY).
MesClientExample/MesClientExample/IOWorker.h: IO 이벤트 생성 및 메인 프레임에 WM_IO_EVENT 전송.
MesClientExample/MesClientExample/MesWorker.h: MES 프로토콜 생성 및 메인 프레임에 WM_MES_REPLY 전송.
MesClientExample/MesClientExample/MesMessages.h / Messages.h: MES 프로토콜 구현 예시

사용법: 실행 후 상태창에서 IO 이벤트와 MES 메세지 확인
