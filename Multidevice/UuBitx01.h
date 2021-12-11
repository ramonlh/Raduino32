// ---------------------------------------------------------------------------

#ifndef UuBitx01H
#define UuBitx01H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "UuBitx02.h"
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Ani.hpp>
#include <FMX.NumberBox.hpp>
#include <IdCustomHTTPServer.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdHTTPServer.hpp>
#include <IdContext.hpp>
#include <IdHeaderList.hpp>
#include <IdServerIOHandler.hpp>
#include <IdServerIOHandlerSocket.hpp>
#include <IdServerIOHandlerStack.hpp>
#include <IdCmdTCPServer.hpp>
#include <IdHTTPProxyServer.hpp>
#include <IdTCPServer.hpp>
#include <Web.HTTPApp.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Memo.Types.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdMessage.hpp>
#include <FMX.Gestures.hpp>

// ---------------------------------------------------------------------------
class TF1 : public TForm {
__published: // IDE-managed Components
	TIdUDPServer *IdUDPServer1;
	TToolBar *ToolBar1;
	TLabel *Label10;
	TSwitch *Switch1;
	TLabel *Label11;
	TLabel *Label57;
	TTabControl *TabControl1;
	TTabItem *TabItem3;
	TEdit *Edit1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label1;
	TLabel *Label5;
	TComboBox *ComboBox13;
	TLabel *Label52;
	TLabel *Label53;
	TLabel *Label54;
	TComboBox *ComboBox15;
	TLabel *Label56;
	TTabItem *TabItem2;
	TTabControl *TabControl3;
	TTabItem *TabItem21;
	TComboBox *ComboBox1;
	TEdit *Edit5;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *Edit6;
	TLabel *Label15;
	TEdit *Edit7;
	TTabItem *TabItem22;
	TLabel *Label16;
	TComboBox *ComboBox2;
	TComboBox *ComboBox4;
	TLabel *Label18;
	TLabel *Label17;
	TComboBox *ComboBox3;
	TComboBox *ComboBox5;
	TSpinBox *SpinBox1;
	TLabel *Label20;
	TLabel *Label19;
	TTabItem *TabItem23;
	TComboBox *ComboBox6;
	TLabel *Label21;
	TSpinBox *SpinBox2;
	TLabel *Label22;
	TSpinBox *SpinBox3;
	TLabel *Label23;
	TSpinBox *SpinBox4;
	TLabel *Label24;
	TLabel *Label25;
	TSpinBox *SpinBox5;
	TTabItem *TabItem24;
	TComboBox *ComboBox7;
	TLabel *Label26;
	TEdit *Edit8;
	TLabel *Label27;
	TEdit *Edit9;
	TLabel *Label28;
	TComboBox *ComboBox8;
	TLabel *Label29;
	TButton *Button2;
	TComboBox *ComboBox9;
	TLabel *Label30;
	TLabel *Label31;
	TTabItem *TabItem25;
	TSpinBox *SpinBox6;
	TLabel *Label32;
	TSpinBox *SpinBox7;
	TLabel *Label33;
	TLabel *Label34;
	TSpinBox *SpinBox8;
	TComboBox *ComboBox14;
	TLabel *Label55;
	TTabItem *TabItem26;
	TSpinBox *SpinBox9;
	TLabel *Label35;
	TLabel *Label36;
	TSpinBox *SpinBox10;
	TLabel *Label37;
	TLabel *Label38;
	TLabel *Label39;
	TSpinBox *SpinBox11;
	TLabel *Label40;
	TSpinBox *SpinBox12;
	TLabel *Label41;
	TLabel *Label42;
	TSpinBox *SpinBox13;
	TLabel *Label43;
	TSpinBox *SpinBox14;
	TLabel *Label44;
	TLabel *Label45;
	TSpinBox *SpinBox15;
	TLabel *Label46;
	TSpinBox *SpinBox16;
	TTabItem *TabItem27;
	TButton *Button3;
	TTabItem *TabItem28;
	TComboBox *ComboBox10;
	TLabel *Label47;
	TButton *Button4;
	TButton *Button5;
	TTabItem *TabItem12;
	TLabel *Label48;
	TComboBox *ComboBox11;
	TComboBox *ComboBox12;
	TLabel *Label49;
	TSpinBox *SpinBox17;
	TLabel *Label50;
	TLabel *Label51;
	TSpinBox *SpinBox18;
	TToolBar *ToolBar2;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TTabItem *TabItem4;
	TMemo *Memo3;
	TButton *Button6;
	TPanel *Panel1;
	TButton *Button7;
	TEdit *Edit2;
	TButton *Button1;
	TTabItem *TabItem1;
	TButton *Button11;
	TButton *Button12;
	TNumberBox *NumberBox1;
	TFloatKeyAnimation *FloatKeyAnimation1;
	TNumberBox *NumberBox2;
	TFloatKeyAnimation *FloatKeyAnimation2;
	TProgressBar *ProgressBar1;
	TLabel *Label58;
	TFrame2 *Frame21;
	TFrame2 *Frame22;
	TFrame2 *Frame23;
	TFrame2 *Frame210;
	TFrame2 *Frame211;
	TFrame2 *Frame212;
	TFrame2 *Frame213;
	TFrame2 *Frame214;
	TFrame2 *Frame215;
	TFrame2 *Frame218;
	TFrame2 *Frame219;
	TFrame2 *Frame220;
	TFrame2 *Frame221;
	TFrame2 *Frame222;
	TFrame2 *Frame223;
	TFrame2 *Frame24;
	TFrame2 *Frame25;
	TFrame2 *Frame26;
	TFrame2 *Frame27;
	TFrame2 *Frame28;
	TFrame2 *Frame29;
	TTimer *Timer1;
	TIdTCPClient *IdTCPClient1;
	TFrame2 *Frame225;
	TLabel *Label59;
	TLabel *Label60;
	TScrollBar *ScrollBar1;
	TScrollBar *ScrollBar2;
	TLabel *Label61;
	TLabel *Label62;
	TNumberBox *NumberBox6;
	TNumberBox *NumberBox7;
	TLabel *Label63;
	TMemo *Memo1;
	TIdUDPServer *IdUDPServer2;
	TNumberBox *NumberBox8;
	TLabel *Label64;
	TLabel *Label65;
	TArcDial *ArcDial1;
	TButton *Button13;
	TButton *Button14;
	TButton *Button15;
	TButton *Button16;
	TButton *Button17;
	TButton *Button18;

	void __fastcall Switch1Switch(TObject *Sender);
	void __fastcall Frame21Text1Click(TObject *Sender);
	void __fastcall Frame22Text1Click(TObject *Sender);
	void __fastcall IdTCPClient1Connected(TObject *Sender);
	void __fastcall IdTCPClient1Disconnected(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Frame23Text1Click(TObject *Sender);
	void __fastcall Frame24Text1Click(TObject *Sender);
	void __fastcall Frame27Text1Click(TObject *Sender);
	void __fastcall Frame28Text1Click(TObject *Sender);
	void __fastcall Frame29Text1Click(TObject *Sender);
	void __fastcall Frame211Text1Click(TObject *Sender);
	void __fastcall Frame214Text1Click(TObject *Sender);
	void __fastcall IdUDPServer1UDPRead(TIdUDPListenerThread *AThread,
		const TIdBytes AData, TIdSocketHandle *ABinding);
	void __fastcall Frame219Text1Click(TObject *Sender);
	void __fastcall ComboBox13Change(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Frame225Text1Click(TObject *Sender);
	void __fastcall NumberBox6Change(TObject *Sender);
	void __fastcall NumberBox7Change(TObject *Sender);
	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall ScrollBar2Change(TObject *Sender);
	void __fastcall Frame217Text1Click(TObject *Sender);
	void __fastcall Frame216Text1Click(TObject *Sender);
	void __fastcall IdUDPServer2UDPRead(TIdUDPListenerThread *AThread,
		const TIdBytes AData, TIdSocketHandle *ABinding);
	void __fastcall NumberBox8MouseWheel(TObject *Sender, TShiftState Shift,
		int WheelDelta, bool &Handled);
	void __fastcall ArcDial1Change(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);

private: // User declarations
public: // User declarations
	__fastcall TF1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TF1 *F1;
// ---------------------------------------------------------------------------
#endif
