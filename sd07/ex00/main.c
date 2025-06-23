#include "contact_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_contact(const t_contact *c)
{
    printf("ID: %d\nName: %s\nPhone: %s\nEmail: %s\nCity: %s\nAddress: %s\n---\n",
        c->id, c->name, c->phone, c->email, c->city, c->address ? c->address : "");
}

static void list_contacts(const t_contact_list *list)
{
    int i = 0;
    if (list->count == 0)
        printf("No contacts found.\n");
    while (i < list->count) {
        print_contact(&list->contacts[i]);
        i++;
    }
}

static void search_menu(const t_contact_list *list)
{
    char buf[256];
    int indices[MAX_CONTACTS];
    int found = 0;
    int by_city = 0;

    printf("Search by (1) Name or (2) City? ");
    if (fgets(buf, sizeof(buf), stdin)) {
        if (buf[0] == '2')
            by_city = 1;
    }
    printf("Enter search substring: ");
    if (fgets(buf, sizeof(buf), stdin)) {
        buf[strcspn(buf, "\n")] = 0;
        if (buf[0]) {
            search_contacts(list, buf, by_city, indices, &found);
            if (found == 0)
                printf("No contacts found.\n");
            else {
                int i = 0;
                while (i < found) {
                    print_contact(&list->contacts[indices[i]]);
                    i++;
                }
            }
        }
    }
}

static void prompt_new_contact(t_contact *c)
{
    char buf[256];
    printf("Name: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    c->name = strdup(buf);

    printf("Phone: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    c->phone = strdup(buf);

    printf("Email: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    c->email = strdup(buf);

    printf("City: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    c->city = strdup(buf);

    printf("Address: ");
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = 0;
    c->address = strdup(buf);
}

static int prompt_id(void)
{
    char buf[32];
    int id = 0;
    printf("Enter contact ID: ");
    if (fgets(buf, sizeof(buf), stdin))
        id = atoi(buf);
    return id;
}

int main(int argc, char **argv)
{
    t_contact_list list;
    int running = 1;
    char buf[32];

    if (argc != 2) {
        printf("Usage: %s <contacts.csv>\n", argv[0]);
        return 1;
    }
    if (!load_contacts(argv[1], &list)) {
        printf("Error: could not open file.\n");
        return 1;
    }

    while (running) {
        printf("\nContact Manager Menu:\n");
        printf("1. List all contacts\n");
        printf("2. Search contacts\n");
        printf("3. Add contact\n");
        printf("4. Update contact\n");
        printf("5. Delete contact\n");
        printf("6. Save and exit\n");
        printf("Choose an option: ");
        if (!fgets(buf, sizeof(buf), stdin))
            continue;

        if (buf[0] == '1') {
            list_contacts(&list);
        } else if (buf[0] == '2') {
            search_menu(&list);
        } else if (buf[0] == '3') {
            t_contact c;
            prompt_new_contact(&c);
            if (add_contact(&list, &c))
                printf("Contact added.\n");
            else
                printf("Failed to add contact.\n");
            free(c.name); free(c.phone); free(c.email); free(c.city); free(c.address);
        } else if (buf[0] == '4') {
            int id = prompt_id();
            t_contact c;
            prompt_new_contact(&c);
            if (update_contact(&list, id, &c))
                printf("Contact updated.\n");
            else
                printf("Contact not found.\n");
            free(c.name); free(c.phone); free(c.email); free(c.city); free(c.address);
        } else if (buf[0] == '5') {
            int id = prompt_id();
            if (delete_contact(&list, id))
                printf("Contact deleted.\n");
            else
                printf("Contact not found.\n");
        } else if (buf[0] == '6') {
            if (save_contacts(argv[1], &list))
                printf("Contacts saved. Exiting.\n");
            else
                printf("Error saving contacts.\n");
            running = 0;
        } else {
            printf("Invalid option.\n");
        }
    }
    free_contact_list(&list);
    return 0;
}