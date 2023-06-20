#include "device_queue.h"

typedef struct node_t
{
    uint8_t tag;
    uint16_t id;
    struct usb_serial_port *port;
    struct node_t *next;
} node_t;

node_t* first_node = NULL;
node_t* last_node = NULL;

uint16_t device_count = 0;
uint16_t last_id = 0;

static node_t* get_node(struct usb_serial_port *port)
{
    node_t* it;

    for (it = first_node; it; it = it->next)
        if (it->port == port)
            break;

    return it;
}

static node_t* get_node_parent(node_t* n)
{
    node_t *parent = first_node;

    if(!parent || n == parent)
        return NULL;

    while (parent->next != n)
        parent = parent->next;

    return parent;
}

static void remove_node(node_t* n)
{
    node_t *parent = get_node_parent(n);

    if(!parent)
        first_node = n->next;
    else if (!n->next)
        parent->next = NULL;  
    else 
        parent->next = n->next;

    if (n == last_node)
    {
        if(parent)
            last_node = parent;
        else
            last_node = first_node;
    }
    
    device_count--;

    kfree(n);
}

static void remove_all_node(void)
{
    node_t* it = first_node;

    while (it)
    {
        node_t* aux = it;

        it = it->next;

        kfree(aux);
    }
}

int device_queue_exist_element(struct usb_serial_port *port)
{
    return get_node(port) != NULL;
}

void device_queue_add(struct usb_serial_port *port, uint8_t tag)
{
    node_t* new_node;

    if(device_queue_exist_element(port))
        return;

    new_node = (node_t*) kzalloc(sizeof(node_t), GFP_KERNEL);

    new_node->tag = tag;
    new_node->port = port;
    new_node->id = last_id++;
    new_node->next = NULL;

    if(!first_node)
    {
        first_node = new_node;
        last_node = new_node;
    }
    else
    {
        last_node->next = new_node;
        last_node = new_node;
    }

    device_count++;
}

void device_queue_remove(struct usb_serial_port *port)
{
    node_t* n = get_node(port);

    if(n)
        remove_node(n);
}

void device_queue_destroy(void)
{
    remove_all_node();
}