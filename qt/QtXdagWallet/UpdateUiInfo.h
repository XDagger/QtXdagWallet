#ifndef UPDATEUIINFO_H
#define UPDATEUIINFO_H

#include "../../xdaglib/wrapper/qtwrapper.h"

#include <QString>

class UpdateUiInfo{

public:
    en_xdag_event_type event_type;
    en_xdag_procedure_type procedure_type;
    en_xdag_program_state xdag_program_state;
    en_balance_load_state balance_state;
    en_address_load_state address_state;

    QString address;
    QString balance;
    QString state;

    operator QVariant() const;
};

Q_DECLARE_METATYPE(UpdateUiInfo);

#endif // UPDATEUIINFO_H
