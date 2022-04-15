#ifndef _FCITX5_MINIMAL_H_
#define _FCITX5_MINIMAL_H_

#include <fcitx-utils/inputbuffer.h>
#include <fcitx/addonfactory.h>
#include <fcitx/addonmanager.h>
#include <fcitx/candidatelist.h>
#include <fcitx/inputcontext.h>
#include <fcitx/inputcontextproperty.h>
#include <fcitx/inputmethodengine.h>
#include <fcitx/inputpanel.h>
#include <fcitx/instance.h>
#include <iconv.h>

class MinCandidateWord : public fcitx::CandidateWord
{
public:
  MinCandidateWord()
  {

  }

  void select(fcitx::InputContext* inputCtx) const override
  {

  }
};

class MinCandidateList : public fcitx::CandidateList,
                         public fcitx::PageableCandidateList
{
public:
  MinCandidateList()
  {

  }

  const fcitx::Text& label(int idx) const
  {

  }

  const fcitx::CandidateWord& candidate(int idx) const
  {

  }

  int size()
  {

  }

  int cursorIndex() const
  {

  }

  fcitx::CandidateLayoutHint layoutHint() const
  {

  }

  bool empty() const
  {

  }

  // Into PageableCandiateList

  bool hasPrev() const
  {

  }

  bool hasNext() const
  {

  }

  void prev()
  {

  }

  void next()
  {

  }

  bool usedNextBefore() const
  {
    
  }
};

class MinEngine : public fcitx::InputMethodEngineV2
{
public:
  MinEngine(fcitx::Instance* instance) : instance_(instance)
  {
  }

  void activate(const fcitx::InputMethodEntry& entry, fcitx::InputContextEvent& ctxEvent)
  {
    inputCtx_ = ctxEvent.inputContext();
  }

  void keyEvent(const fcitx::InputMethodEntry& entry, fcitx::KeyEvent* keyEvent)
  {
    // We only accept a-z
    if (keyEvent->key().isLAZ()) {
      keyEvent->accept();
      auto keyStr = keyEvent->key().toString();
    }
  }

  void reset(const fcitx::InputMethodEntry& entry, fcitx::InputContextEvent& ctxEvent)
  {
  }
private:
  fcitx::Instance* instance_;
  fcitx::InputContext* inputCtx_;
};

#endif // _FCITX5_MINIMAL_H_