#include "pulseform.h"

QList<FormLines> PulseForm::InitializePulseForm()
{
  qreal _pulse_form_width = 185;
  qreal _pulse_form_height = 85;
  QList <FormLines> pulseForm;
  FormLines tmp;
  tmp.lower = 0;
  tmp.upper = 80;
  tmp.tail = QPointF(0,38);
  tmp.head = QPointF(80,38);
  pulseForm.push_back(tmp);

  tmp.lower = 80;
  tmp.upper = 83;
  tmp.tail = QPointF(80,38);
  tmp.head = QPointF(83,48);
  pulseForm.push_back(tmp);

  tmp.lower = 83;
  tmp.upper = 90;
  tmp.tail = QPointF(83,48);
  tmp.head = QPointF(90,34);
  pulseForm.push_back(tmp);

  tmp.lower = 90;
  tmp.upper = 93;
  tmp.tail = QPointF(90,34);
  tmp.head = QPointF(93,66);
  pulseForm.push_back(tmp);

  tmp.lower = 93;
  tmp.upper = 97;
  tmp.tail = QPointF(93,66);
  tmp.head = QPointF(97,13);
  pulseForm.push_back(tmp);

  tmp.lower = 97;
  tmp.upper = 103;
  tmp.tail = QPointF(97,13);
  tmp.head = QPointF(103,38);
  pulseForm.push_back(tmp);

  tmp.lower = 103;
  tmp.upper = 107;
  tmp.tail = QPointF(103,38);
  tmp.head = QPointF(107,33);
  pulseForm.push_back(tmp);

  tmp.lower = 107;
  tmp.upper = 114;
  tmp.tail = QPointF(107,33);
  tmp.head = QPointF(114,38);
  pulseForm.push_back(tmp);

  tmp.lower = 114;
  tmp.upper = _pulse_form_width;
  tmp.tail = QPointF(114,38);
  tmp.head = QPointF(_pulse_form_width,38);
  pulseForm.push_back(tmp);
  return pulseForm;
}
