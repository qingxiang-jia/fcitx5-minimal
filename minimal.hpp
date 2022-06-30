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
#include <string>
#include <array>

const static int displayCandCnt = 10;

class MinCandidateWord : public fcitx::CandidateWord
{
public:
  MinCandidateWord(std::string value)
  {
    setText(fcitx::Text(std::move(value)));
  }

  void select(fcitx::InputContext* inputCtx) const override
  {
    inputCtx->commitString(text().toString());

    // Reset UI
    inputCtx->inputPanel().reset();
    inputCtx->updateUserInterface(fcitx::UserInterfaceComponent::InputPanel);
    inputCtx->updatePreedit();
  }
};

class MinCandidateList : public fcitx::CandidateList
{
private:
  std::array<std::shared_ptr<MinCandidateWord>, displayCandCnt> candidates_;
  std::array<std::shared_ptr<fcitx::Text>, displayCandCnt> labels_;

public:
  MinCandidateList(std::array<std::string, displayCandCnt> candidateStrs)
  {
    // Box strings into MinCandidateWord
    for (int i = 0; i < displayCandCnt; i++) {
      auto word = std::shared_ptr<MinCandidateWord>(new MinCandidateWord(candidateStrs[i]));
      candidates_[0] = word;
    }

    // Generate labels
    for (int i = 0; i < displayCandCnt; i++) {
      auto label = std::shared_ptr<fcitx::Text>(new fcitx::Text(std::to_string(i + 1) + ".")); // Label looks like 1. 2. 3. ...
      labels_[i] = label;
    }
  }

  const fcitx::Text& label(int idx) const
  {
    return *labels_[idx];
  }

  const fcitx::CandidateWord& candidate(int idx) const
  {
    return *candidates_[idx];
  }

  int size()
  {
    return candidates_.size();
  }

  int cursorIndex() const
  {
    return 0; // TODO: is this right?
  }

  fcitx::CandidateLayoutHint layoutHint() const
  {
    return fcitx::CandidateLayoutHint::Horizontal;
  }

  bool empty() const
  {
    return false; // TODO: is this right?
  }
};

class MinEngine : public fcitx::InputMethodEngineV2
{
private:
  std::shared_ptr<fcitx::Instance> instance_;
  std::shared_ptr<fcitx::InputContext> inputCtx_;
  std::shared_ptr<std::vector<char>> inputBuf_;

public:
  MinEngine(fcitx::Instance* instance) : instance_(instance)
  {
  }

  void activate(const fcitx::InputMethodEntry& entry, fcitx::InputContextEvent& ctxEvent)
  {
    inputCtx_ = std::shared_ptr<fcitx::InputContext>(ctxEvent.inputContext());
  }

  void keyEvent(const fcitx::InputMethodEntry& entry, fcitx::KeyEvent* keyEvent)
  {
    // We only accept a-z
    if (keyEvent->key().isLAZ()) {
      keyEvent->accept();
      auto keyStr = keyEvent->key().toString();

      // Add the character to inputBuf_
      inputBuf_->push_back(*keyStr.data());

      // Generate candidates
      std::vector<std::string> candStrs = genCandidates();
      std::unique_ptr<fcitx::CandidateList> candList = std::make_unique<MinCandidateList>(candStrs); // If use auto, next line will complaint. If not use auto, it complains a different problem.
      inputCtx_->inputPanel().setCandidateList(candList);//TODO

      // Set preedit
      //TODO
    }
  }

  // Every candidate is the same: the stuff the user just typed in.
  std::vector<std::string> genCandidates()
  {
    std::vector<std::string> candidates;
    for (int i = 0; i < displayCandCnt; i++) {
      std::string cand(inputBuf_->begin(), inputBuf_->end());
      candidates.push_back(std::move(cand));
    }
    return candidates;
  }

  void reset(const fcitx::InputMethodEntry& entry, fcitx::InputContextEvent& ctxEvent)
  {
  }
};

#endif // _FCITX5_MINIMAL_H_