#pragma once

//Sending Signals
#define ASK_FOR_NEW_CARRIERID_SIGNAL			QByteArray::fromHex("FFFFFFFF20FFFF20")
#define PARDON_SIGNAL						QByteArray::fromHex("FFFFFFFF21FFFF21")

//Received Signals
#define CARRIERID_TO_CHECK_SIGNAL			QByteArray::fromHex("FFFFFFFF40FFFF40")

#define signalNumByte		8