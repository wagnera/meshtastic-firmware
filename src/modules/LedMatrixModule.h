#pragma once
#include "SinglePortModule.h"
#include "concurrency/OSThread.h"

/**
 * A module that provides easy low-level remote access to device hardware.
 */
class LedMatrixModule : public SinglePortModule, private concurrency::OSThread
{
    

  public:
    /** Constructor
     * name is for debugging output
     */
    LedMatrixModule();

  protected:
    /** Called to handle a particular incoming message

    @return true if you've guaranteed you've handled this message and no other handlers should be considered for it
    */
    virtual ProcessMessage handleReceived(const meshtastic_MeshPacket &mp) override;

    virtual bool wantPacket(const meshtastic_MeshPacket *p) override;

    /**
     * Periodically read the gpios we have been asked to WATCH, if they have changed,
     * broadcast a message with the change information.
     *
     * The method that will be called each time our thread gets a chance to run
     *
     * Returns desired period for next invocation (or RUN_SAME for no change)
     */
    virtual int32_t runOnce() override;
};

extern LedMatrixModule *ledMatrixModule;
