#include "zexception.h"

zException::zException(void) {this->name = "Unknown";}
zException:: zException(QString n) {this->name = n;}
void zException::raise() const { throw *this; }
zException *zException::clone() const { return new zException(*this); }

