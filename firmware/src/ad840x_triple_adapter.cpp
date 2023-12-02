#include "adapters.h"

static inline void ad840x_triple_set(AD840X *pots, AD840XAddress addr1, AD840XAddress addr2, AD840XAddress addr3, uint16_t data)
{
    if (511 <= data)
    {
        return;
    }

    if (data < 256)
    {
        ad840x_set(pots, addr1, 0);
        ad840x_set(pots, addr2, 0);
        ad840x_set(pots, addr3, data);
    }
    else
    {
        ad840x_set(pots, addr1, data - 255);
        ad840x_set(pots, addr2, data - 255);
        ad840x_set(pots, addr3, 255);
    }
}

static void ad840x_triple_adapter_set_wiper_position(NcmDigitalPotentiometerInterface *parent, double position)
{
    AD840XTripleAdapter *self = (AD840XTripleAdapter *)parent;
    if (self == NULL)
    {
        return;
    }

    ad840x_triple_set(self->pots, self->addr1, self->addr2, self->addr3, (uint16_t)(510 * position));
}

static void ad840x_triple_adapter_power_on(NcmDigitalPotentiometerInterface *parent)
{
    AD840XTripleAdapter *self = (AD840XTripleAdapter *)parent;
    if (self == NULL)
    {
        return;
    }

    ad840x_power_on(self->pots);
}

static void ad840x_triple_adapter_shutdown(NcmDigitalPotentiometerInterface *parent)
{
    AD840XTripleAdapter *self = (AD840XTripleAdapter *)parent;
    if (self == NULL)
    {
        return;
    }

    ad840x_shutdown(self->pots);
}

AD840XTripleAdapter *ad840x_triple_adapter_new(AD840X *pots, AD840XAddress addr1, AD840XAddress addr2, AD840XAddress addr3)
{
    if (pots == NULL)
    {
        return NULL;
    }

    AD840XTripleAdapter *self = (AD840XTripleAdapter *)malloc(sizeof(AD840XTripleAdapter));
    if (self == NULL)
    {
        return NULL;
    }

    self->parent.set_wiper_position = ad840x_triple_adapter_set_wiper_position;
    self->parent.power_on = ad840x_triple_adapter_power_on;
    self->parent.shutdown = ad840x_triple_adapter_shutdown;

    self->pots = pots;
    self->addr1 = addr1;
    self->addr2 = addr2;
    self->addr3 = addr3;

    return self;
}

void ad840x_triple_adapter_delete(AD840XTripleAdapter *self)
{
    if (self == NULL)
    {
        return;
    }
    
    free(self);
}