#pragma once

#include "queueTad.h"
#include "listTad.h"
#include "queueAvg.h"

void queuePatients(PtList patients);
void showQueueMenu(PtQueue ptQueue);
void getDataAvg(PtList list, int listSize, QueueAvg* queueAvg);
void creteQueuePatients(PtQueue ptQueue, PtList patients, int listSize, QueueAvg* queueAvg);
