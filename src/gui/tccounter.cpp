#include <tianchi/gui/tccounter.h>
#include <tianchi/gui/tcarrowbutton.h>

#include <QEvent>
#include <QLineEdit>
#include <QHBoxLayout>

class TcCounterPrivate
{
    Q_DECLARE_PUBLIC(TcCounter)
public:
    explicit TcCounterPrivate(TcCounter *qptr);
    ~TcCounterPrivate();

    /// @brief ��ʼ��
    void initcounter();

    /// @brief ����arrowButton��״̬
    void updateButtons();

    /// @brief ��ʾvalueEdit��ֵ
    void showNumbers(double value);

    TcCounter* const q_ptr;
    enum Button
    {
        Button1,
        Button2,
        Button3,
        //��ť����
        ButtonCnt
    };

    TcArrowButton *downButton[ButtonCnt];
    TcArrowButton *upButton[ButtonCnt];
    QLineEdit *valueEdit;

    int buttonNum;
    double singleStep;
    double maximum;
    double minimum;
    double value;
    bool isValid;

};

TcCounterPrivate::TcCounterPrivate(TcCounter *qptr): q_ptr(qptr)
{
}

TcCounterPrivate::~TcCounterPrivate()
{
}

/// @brief ���캯������ʼlineedit��ֵ�ķ�Χ��0.0-1.0������0.01��״̬Ϊ�����ã�
///        Ĭ�ϵİ�ť������������
/// @param parent
TcCounter::TcCounter(QWidget *parent)
    : QWidget(parent), d_ptr(new TcCounterPrivate(this))
{
    Q_D(TcCounter);
    d->initcounter();
}

TcCounter::~TcCounter()
{
    delete d_ptr;
}

/// @brief ��ʼ�����
void TcCounterPrivate::initcounter()
{
    Q_Q(TcCounter);
    QHBoxLayout *layout = new QHBoxLayout(q);
    layout->setMargin(0);
    layout->setSpacing(0);

    //valueEdit��ఴť
    for (int i = ButtonCnt - 1; i >= 0; i--)
    {
        TcArrowButton *lbtn = new TcArrowButton(i + 1, Qt::DownArrow, q);
        lbtn->setFocusPolicy(Qt::NoFocus);
        //lbtn->installEventFilter(this);
        lbtn->setMinimumWidth(12);
        lbtn->setMaximumWidth(12);
        lbtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        layout->addWidget(lbtn);

        downButton[i] = lbtn;
    }

    //�м��valueEdit
    valueEdit = new QLineEdit(q);
    valueEdit->setReadOnly(true);
    layout->addWidget(valueEdit);

    //valueEdit�Ҳఴť
    for (int i = 0; i <= ButtonCnt -1; i++)
    {
        TcArrowButton *rbtn = new TcArrowButton(i + 1, Qt::UpArrow, q);
        rbtn->setFocusPolicy(Qt::NoFocus);
        rbtn->setMinimumWidth(12);
        rbtn->setMaximumWidth(12);
        rbtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        //rbtn->installEventFilter(this);
        layout->addWidget(rbtn);

        upButton[i] = rbtn;
    }

    q->setButtonNum(2);
    q->setRange(0.0, 1.0);
    q->setSingleStep(0.001);

    //����FocusProxy��FocusPolicy
    q->setFocusProxy(valueEdit);
    q->setFocusPolicy(Qt::StrongFocus);

    q->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
}

/// @brief ���ð�ť����
void TcCounter::setButtonNum(int buttonNum)
{
    Q_D(TcCounter);
    if (buttonNum < 0 || buttonNum > d->ButtonCnt)
    {
        return;
    }
    for (int i = 0; i < d->ButtonCnt; i++)
    {
        if (i < buttonNum)
        {
            d->downButton[i]->show();
            d->upButton[i]->show();
        }
        else
        {
            d->downButton[i]->hide();
            d->upButton[i]->hide();
        }
    }

    d->buttonNum = buttonNum;
}

/// @brief ����valueEdit��Χ
void TcCounter::setRange(double minnum, double maxnum)
{
    Q_D(TcCounter);
    maxnum = qMax(minnum, maxnum);
    if (d->minimum == minnum && d->maximum == maxnum)
    {
        return;
    }

    //���������Сֵ
    d->minimum = minnum;
    d->maximum = maxnum;

    //���ò���
    setSingleStep(singleStep());

    const double value = qBound(minnum, d->value, maxnum);

    if (value != d->value)
    {
        //����valueֵ
        d->value = value;

        if (d->isValid)
        {
            d->showNumbers(d->value);
            Q_EMIT valueChanged(d->value);
        }
    }
}

/// @brief ���ò���
void TcCounter::setSingleStep(double step)
{
    Q_D(TcCounter);
    d->singleStep = qMax(step, 0.0);
}

/// @brief ���ز���ֵ
double TcCounter::singleStep() const
{
    Q_D(const TcCounter);
    return d->singleStep;
}

/// @brief ����״̬
void TcCounter::setValid(bool on)
{
    Q_D(TcCounter);
    if (on == d->isValid)
    {
        return;
    }

    //����isValid��ֵ
    d->isValid = on;

    d->updateButtons();

    if (d->isValid)
    {
        d->showNumbers(d->value);
        Q_EMIT valueChanged(d->value);
    }
    else
    {
        d->valueEdit->setText(QString::null);
    }
}

/// @brief ���°�ť״̬
void TcCounterPrivate::updateButtons()
{
    if (isValid)
    {
        for (int i = 0; i < ButtonCnt; i++)
        {
            upButton[i]->setEnabled(value > minimum);
            downButton[i]->setEnabled(value < maximum);
        }
    }
    else
    {
        for (int i = 0; i < ButtonCnt; i++)
        {
            upButton[i]->setEnabled(false);
            downButton[i]->setEnabled(false);
        }
    }
}

/// @brief ��ʾvalueEdit��ֵ
void TcCounterPrivate::showNumbers(double value)
{
    QString text;
    text.setNum(value);
    valueEdit->setText(text);
}

#include "moc_tccounter.cpp"
