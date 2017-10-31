///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 Edouard Griffiths, F4EXB                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef SDRBASE_DEVICE_DEVICESOURCEAPI_H_
#define SDRBASE_DEVICE_DEVICESOURCEAPI_H_

#include <stdint.h>
#include <QObject>
#include <QString>

#include "dsp/dspdevicesourceengine.h"

#include "util/export.h"

class BasebandSampleSink;
class ThreadedBasebandSampleSink;
class DeviceSampleSource;
class MessageQueue;
class PluginInstanceGUI;
class PluginInterface;
class Preset;
class DeviceSinkAPI;

class SDRANGEL_API DeviceSourceAPI : public QObject {
    Q_OBJECT

public:
    DeviceSourceAPI(int deviceTabIndex,
            DSPDeviceSourceEngine *deviceSourceEngine);
    ~DeviceSourceAPI();

    // Device engine stuff
    void addSink(BasebandSampleSink* sink);       //!< Add a sample sink to device engine
    void removeSink(BasebandSampleSink* sink);    //!< Remove a sample sink from device engine
    void addThreadedSink(ThreadedBasebandSampleSink* sink);     //!< Add a sample sink that will run on its own thread to device engine
    void removeThreadedSink(ThreadedBasebandSampleSink* sink);  //!< Remove a sample sink that runs on its own thread from device engine
    void setSampleSource(DeviceSampleSource* source); //!< Set device sample source
    DeviceSampleSource *getSampleSource();      //!< Return pointer to the device sample source
    bool initAcquisition();               //!< Initialize device engine acquisition sequence
    bool startAcquisition();              //!< Start device engine acquisition sequence
    void stopAcquisition();               //!< Stop device engine acquisition sequence
    DSPDeviceSourceEngine::State state() const; //!< device engine state
    QString errorMessage();               //!< Return the current device engine error message
    uint getDeviceUID() const;            //!< Return the current device engine unique ID
    MessageQueue *getDeviceEngineInputMessageQueue();
    MessageQueue *getSampleSourceInputMessageQueue();
    MessageQueue *getSampleSourceGUIMessageQueue();
    void configureCorrections(bool dcOffsetCorrection, bool iqImbalanceCorrection); //!< Configure current device engine DSP corrections

    void setHardwareId(const QString& id);
    void setSampleSourceId(const QString& id);
    void resetSampleSourceId();
    void setSampleSourceSerial(const QString& serial);
    void setSampleSourceDisplayName(const QString& serial);
    void setSampleSourceSequence(int sequence);
    void setSampleSourcePluginInterface(PluginInterface *iface);
    void setSampleSourcePluginInstanceGUI(PluginInstanceGUI *gui);

    const QString& getHardwareId() const { return m_hardwareId; }
    const QString& getSampleSourceId() const { return m_sampleSourceId; }
    const QString& getSampleSourceSerial() const { return m_sampleSourceSerial; }
    const QString& getSampleSourceDisplayName() const { return m_sampleSourceDisplayName; }
    PluginInterface *getPluginInterface() { return m_pluginInterface; }
    uint32_t getSampleSourceSequence() const { return m_sampleSourceSequence; }
    PluginInstanceGUI *getSampleSourcePluginInstanceGUI() { return m_sampleSourcePluginInstanceUI; }

    void loadSourceSettings(const Preset* preset);
    void saveSourceSettings(Preset* preset);

    DSPDeviceSourceEngine *getDeviceSourceEngine() { return m_deviceSourceEngine; }

    const std::vector<DeviceSourceAPI*>& getSourceBuddies() const { return m_sourceBuddies; }
    const std::vector<DeviceSinkAPI*>& getSinkBuddies() const { return m_sinkBuddies; }
    void addSourceBuddy(DeviceSourceAPI* buddy);
    void addSinkBuddy(DeviceSinkAPI* buddy);
    void removeSourceBuddy(DeviceSourceAPI* buddy);
    void removeSinkBuddy(DeviceSinkAPI* buddy);
    void clearBuddiesLists();
    void *getBuddySharedPtr() const { return m_buddySharedPtr; }
    void setBuddySharedPtr(void *ptr) { m_buddySharedPtr = ptr; }
    bool isBuddyLeader() const { return m_isBuddyLeader; }
    void setBuddyLeader(bool isBuddyLeader) { m_isBuddyLeader = isBuddyLeader; }

    const QTimer& getMasterTimer() const { return m_masterTimer; } //!< This is the DSPEngine master timer

protected:
    int m_deviceTabIndex;
    DSPDeviceSourceEngine *m_deviceSourceEngine;

    QString m_hardwareId;
    QString m_sampleSourceId;
    QString m_sampleSourceSerial;
    QString m_sampleSourceDisplayName;
    uint32_t m_sampleSourceSequence;
    PluginInterface* m_pluginInterface;
    PluginInstanceGUI* m_sampleSourcePluginInstanceUI;

    std::vector<DeviceSourceAPI*> m_sourceBuddies; //!< Device source APIs referencing the same physical device
    std::vector<DeviceSinkAPI*> m_sinkBuddies;     //!< Device sink APIs referencing the same physical device
    void *m_buddySharedPtr;
    bool m_isBuddyLeader;
    const QTimer& m_masterTimer; //!< This is the DSPEngine master timer

    friend class DeviceSinkAPI;
};


#endif /* SDRBASE_DEVICE_DEVICESOURCEAPI_H_ */
