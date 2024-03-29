#pragma once

#include "queueTad.h"
#include "listTad.h"
#include "queueAvg.h"

void getDataAvg(PtList list, int listSize, QueueAvg* queueAvg);
void creteQueuePatients(PtQueue ptQueue, PtList patients, int listSize, QueueAvg* queueAvg);
void nextQueueCommand(PtQueue ptQueue);
void showQueueMenu(PtQueue patientsQueue);
void initializeQueue(PtList patients);
