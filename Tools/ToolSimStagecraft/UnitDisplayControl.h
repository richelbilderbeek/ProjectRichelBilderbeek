//---------------------------------------------------------------------------

#ifndef UnitDisplayControlH
#define UnitDisplayControlH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
struct AudioSignalDisplay;
struct LcdSymbol;
struct Led;
namespace Extctrls { struct TImage; }
//---------------------------------------------------------------------------
struct DisplayControl
{
  DisplayControl(Extctrls::TImage * const image);
  virtual void Update() = 0;

  protected:
  Extctrls::TImage * const mImage;

  //DisplayControl can only be deleted by boost::shared_ptr
  //or descendants
  virtual ~DisplayControl() {}
  friend boost::checked_delete(DisplayControl *);
};
//---------------------------------------------------------------------------
struct AudioSignalControl : public DisplayControl
{
  AudioSignalControl(
    const boost::shared_ptr<AudioSignalDisplay> audioSignalDisplay,
    Extctrls::TImage * const image);

  void Update();

  private:
  const boost::shared_ptr<AudioSignalDisplay> mAudioSignalDisplay;

  //AudioSignalControl can only be deleted by boost::shared_ptr
  ~AudioSignalControl() {}
  friend boost::checked_delete(AudioSignalControl*);
};
//---------------------------------------------------------------------------
struct LcdSymbolControl : public DisplayControl
{
  LcdSymbolControl(const boost::shared_ptr<LcdSymbol> lcdSymbol,
    Extctrls::TImage * const image,
    Extctrls::TImage * const imageLcdSymbol);

  void Update();

  private:

  const boost::shared_ptr<LcdSymbol> mLcdSymbol;
  Extctrls::TImage * const mImageLcdSymbol;

  protected:
  //LcdSymbolControl can only be deleted by boost::shared_ptr
  //or descendants
  virtual ~LcdSymbolControl() {}
  friend boost::checked_delete(LcdSymbolControl *);
};
//---------------------------------------------------------------------------
struct LcdSymbolPlayControl : public LcdSymbolControl
{
  LcdSymbolPlayControl(const boost::shared_ptr<LcdSymbol> lcdSymbol,
    Extctrls::TImage * const image);

  private:
  //LcdSymbolPlayControl can only be deleted by boost::shared_ptr
  ~LcdSymbolPlayControl() {}
  friend boost::checked_delete(LcdSymbolPlayControl *);
};
//---------------------------------------------------------------------------
struct LcdSymbolRecControl : public LcdSymbolControl
{
  LcdSymbolRecControl(const boost::shared_ptr<LcdSymbol> lcdSymbol,
    Extctrls::TImage * const image);

  private:
  //LcdSymbolRecControl can only be deleted by boost::shared_ptr
  ~LcdSymbolRecControl() {}
  friend boost::checked_delete(LcdSymbolRecControl *);
};
//---------------------------------------------------------------------------
struct LedControl : public DisplayControl
{
  LedControl(const boost::shared_ptr<Led> led,
    Extctrls::TImage * const image);

  void Update();

  private:
  const boost::shared_ptr<Led> mLed;

  //LedControl can only be deleted by boost::shared_ptr
  ~LedControl() {}
  friend boost::checked_delete(LedControl *);
};
//---------------------------------------------------------------------------

#endif
