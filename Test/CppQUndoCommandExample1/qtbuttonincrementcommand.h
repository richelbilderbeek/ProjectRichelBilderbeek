#ifndef QTBUTTONINCREMENTCOMMAND_H
#define QTBUTTONINCREMENTCOMMAND_H

#include <QUndoCommand>

struct QPushButton;

struct QtButtonIncrementCommand : public QUndoCommand
{
  explicit QtButtonIncrementCommand(QPushButton * const button);
  QtButtonIncrementCommand(const QtButtonIncrementCommand&) = delete;
  QtButtonIncrementCommand& operator=(const QtButtonIncrementCommand&) = delete;

  ///Virtual function supplied by QUndoCommand
  void redo() override;

  ///Virtual function supplied by QUndoCommand
  void undo() override;

  private:
  QPushButton * const m_button;

};

#endif // QTBUTTONINCREMENTCOMMAND_H
