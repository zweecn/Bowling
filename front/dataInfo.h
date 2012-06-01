#ifndef _DATA_INFO_H
#define _DATA_INFO_H
#include <QString>
#include <QVector>
namespace dataTransform
{
    enum
    {
        CALL_SERVICE = 0xFF01,
        CALL_BEGIN = 0xFF02,
        ROW_SCORE = 0xFF03,
        END_ONE = 0xFF04,
        CALL_GOODS = 0xFF05,

        ANS_YES_YOU_CAN_BEGIN = 0xFF11,
        ANS_NO_DO_NOT_BEGIN = 0xFF22,
        ANS_YOU_CAN_EXCHANGE_ROW = 0xFF13,
        ANS_INIT_SCORE = 0xFF14,
        ANS_CLEAR_SCORE  = 0xFF15,
        ANS_AFTER_ADD_MONEY = 0xFF16,
        ANS_DISMISS = 0xFF17,

        IS_VIP,
        NOT_VIP,
        GET_REST,
        NO_USE,

        SCORE_SIZE = 10,
        BT_ROW_SIZE = 4,
        BOWLING_PORT = 6789
    };

    class ScoreInfo
    {
    public:
        int theEndFlag;
        //int totalPlayerCount;
        //int currentPlayerNo;
        int turn;
        int score[SCORE_SIZE];
        QString str[SCORE_SIZE];

        int bt[BT_ROW_SIZE][SCORE_SIZE];
    };


    class GoodsInfo
    {
    public:
        int goodsTypeSize;
        QVector<int> goodsId;
        QVector<int> goodsCount;
    };

}

#endif
