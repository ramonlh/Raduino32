// ---------------------------------------------------------------------------

#ifndef UuBitx02H
#define UuBitx02H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>

// ---------------------------------------------------------------------------
class TFrame2 : public TFrame {
__published: // IDE-managed Components
	TText *Text1;
	TRectangle *Rectangle1;

private: // User declarations
public: // User declarations
	__fastcall TFrame2(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TFrame2 *Frame2;
// ---------------------------------------------------------------------------
#endif
