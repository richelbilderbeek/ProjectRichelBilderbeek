#ifndef QTBUTTONINCREMENTCOMMAND_H
#define QTBUTTONINCREMENTCOMMAND_H

#include <QUndoCommand>

struct QPushButton;

struct QtButtonIncrementCommand : public QUndoCommand
{
  explicit QtButtonIncrementCommand(QPushButton * const button);

  ///Virtual function supplied by QUndoCommand
  void redo();

  ///Virtual function supplied by QUndoCommand
  void undo();

  private:
  QPushButton * const m_button;

};

#endif // QTBUTTONINCREMENTCOMMAND_H
