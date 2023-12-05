#ifndef PULSEFORM_H
#define PULSEFORM_H

#include <QWidget>
#include <QList>

static qreal _pulse_form_width = 185;
static qreal _pulse_form_height = 85;

struct FormLines
{
  qreal upper;
  qreal lower;
  qreal k;
  qreal c;
  QPointF tail;
  QPointF head;
};

class PulseForm
{
  public:
    static QList <FormLines> InitializePulseForm();
};
#endif // PULSEFORM_H
