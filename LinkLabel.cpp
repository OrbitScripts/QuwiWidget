#include "LinkLabel.h"

#include <QDebug>

LinkLabel::LinkLabel(QWidget* parent, Qt::WindowFlags f)
  : QLabel(parent, f)
{

}

void LinkLabel::enterEvent(QEvent*) {
  QString style = text();
  style.replace("text-decoration: none", "text-decoration: underline");
  style.replace("color:#76a1e1", "color:#83a6d9");
  setText(style);
}

void LinkLabel::leaveEvent(QEvent*) {
  QString style = text();
  style.replace("text-decoration: underline", "text-decoration: none");
  style.replace("color:#83a6d9", "color:#76a1e1");
  setText(style);
}
