// �ĵ�˵����ʵ�ֿ������߰�ť���ڴ�С��counter
// ==========================================================================
// ������־��
// ����         ��Ա        ˵��
// --------------------------------------------------------------------------
// 2013.10.31   younghz     ����
// ==========================================================================
/// @file tccounter.h ʵ�ֿ������߰�ť���ڴ�С��counter
// ==========================================================================

#ifndef TIANCHI_TCCOUNTER_H
#define TIANCHI_TCCOUNTER_H

#include <tianchi/tcglobal.h>
#include <QWidget>

/// @brief counter widget
/// ���widget����һ����ʾ���ֵ�lineedit��һ�����߶�������������Ӻͼ�С��ʾ�����ֵ�ֵ��
/// arrowbutton����ť����ʱ���ӻ��Ǽ�С����ֵ������setIncSteps()�����趨��lineedit����
/// ��arrowbutton�ĸ���������setNumButtons()�����趨��

class TcCounterPrivate;

/// @brief TcCounter��
class TIANCHI_API TcCounter : public QWidget
{
    Q_OBJECT
public:
    /// @brief ���캯��
    explicit TcCounter(QWidget *parent = 0);
    ~TcCounter();

    /// @brief ���ð�ť����
    /// @param [in] ��ť����ֵ
    void setButtonNum(int n);

    /// @brief ����valueEdit��ʾ���ķ�Χ
    /// @param [in] minnum ��Сֵ
    /// @param [in] maxnum ���ֵ
    void setRange(double minnum, double maxnum);

    /// @brief ���ò���
    /// @param [in] ����ֵ
    void setSingleStep(double step);

    /// @return ������С
    double singleStep() const;

    /// @brief ����counter��״̬����Ч����Ч��
    ///        ������Ϊ��Чʱ��lineEdit�в�����ʾ���ֲ������ߵ�arrowButton������
    /// @param [in] on Ϊtrueʱ״̬����Ч��������Ч
    void setValid(bool on);

    /// @brief �����Ƿ���Ч״̬
    bool isValid() const;
Q_SIGNALS:

    /// @brief ���ؼ���ֵ�ı�ʱ����
    /// @param value �µ�ֵ
    void valueChanged(double value);

private:
    Q_DISABLE_COPY(TcCounter)
    Q_DECLARE_PRIVATE(TcCounter)

    TcCounterPrivate* const d_ptr;
};

#endif // TIANCHI_TCCOUNTER_H
