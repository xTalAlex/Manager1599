/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerNotational.h"

struct notational notational_layer;

struct notational loadNotational(){
    loadGraphicInstanceGroup();
    loadNotationInstanceGroup();
    
    return notational_layer;
}

void loadGraphicInstanceGroup(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    xmlNodePtr temp_cur;
    
    struct graphic_instance_group* graphic_instance_group_temp=NULL;
    struct graphic_instance_group* graphic_instance_group_head=NULL;
    struct graphic_instance_group* graphic_instance_group_p=NULL;
    notational_layer.n_graphic_insance_groups=0;
    
    xpath=(xmlChar *)"/ieee1599/notational/graphic_instance_group";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning graphic_instance_groups 
            graphic_instance_group_temp=(struct graphic_instance_group*)calloc(1,sizeof(struct graphic_instance_group));
            cur=nodeset->nodeTab[i];
            attributes=cur->properties;    
            if (graphic_instance_group_temp) {
                while (attributes != NULL) {
                    if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                        graphic_instance_group_temp->description = xmlGetProp(cur, attributes->name);
                    }
                    attributes = attributes->next;
                }
                //load graphic_instance list
                struct graphic_instance* graphic_instance_temp = NULL;
                struct graphic_instance* graphic_instance_head = NULL;
                struct graphic_instance* graphic_instance_p = NULL;
                graphic_instance_group_temp->n_graphic_instances = 0;

                temp_cur = cur->xmlChildrenNode;
                while (temp_cur != NULL) {
                    if (!xmlStrcmp(temp_cur->name, (const xmlChar*)"graphic_instance")) {
                        graphic_instance_temp = (struct graphic_instance*)calloc(1, sizeof(struct graphic_instance));

                        if (graphic_instance_temp) {
                            graphic_instance_temp = loadGraphicInstance(temp_cur);

                            graphic_instance_temp->next_graphic_instance = NULL;
                            if (graphic_instance_head == NULL)
                                graphic_instance_head = graphic_instance_temp;
                            else {
                                graphic_instance_p = graphic_instance_head;
                                while (graphic_instance_p->next_graphic_instance != NULL)
                                    graphic_instance_p = graphic_instance_p->next_graphic_instance;
                                graphic_instance_p->next_graphic_instance = graphic_instance_temp;
                            }
                            graphic_instance_group_temp->n_graphic_instances++;
                        }
                        else { fprintf(stderr, "Memory allocation failed for 'graphic_instance' element\n"); }
                    }
                    temp_cur = temp_cur->next;
                }
                graphic_instance_group_temp->graphic_instance = graphic_instance_head;

                graphic_instance_group_temp->next_graphic_instance_group = NULL;
                if (graphic_instance_group_head == NULL)
                    graphic_instance_group_head = graphic_instance_group_temp;
                else {
                    graphic_instance_group_p = graphic_instance_group_head;
                    while (graphic_instance_group_p->next_graphic_instance_group != NULL)
                        graphic_instance_group_p = graphic_instance_group_p->next_graphic_instance_group;
                    graphic_instance_group_p->next_graphic_instance_group = graphic_instance_group_temp;
                }
                notational_layer.n_graphic_insance_groups++;
            }
            else { fprintf(stderr, "Memory allocation failed for 'graphic_instance_group' element\n"); }
        }
    }
    notational_layer.graphic_instance_group = graphic_instance_group_head;
}

struct graphic_instance* loadGraphicInstance(xmlNodePtr cur){
    struct graphic_instance* value=(struct graphic_instance*)calloc(1, sizeof(struct graphic_instance));
    xmlAttr* attributes;

    if (value) {
        struct graphic_event* graphic_event_temp = NULL;
        struct graphic_event* graphic_event_head = NULL;
        struct graphic_event* graphic_event_p = NULL;
        value->n_graphic_events = 0;

        value->next_graphic_instance = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                value->description = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"position_in_group")) {
                value->position_in_group = xmlCharToInt(xmlGetProp(cur, attributes->name));
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_name")) {
                value->file_name = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_format")) {
                value->file_format = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"encoding_format")) {
                value->encoding_format = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"measurement_unit")) {
                value->measurement_unit = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"graphic_event")) {
                graphic_event_temp = (struct graphic_event*)calloc(1, sizeof(struct graphic_event));

                if (graphic_event_temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                            graphic_event_temp->event_ref = xmlGetProp(cur, attributes->name);
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"upper_left_x")) {
                            graphic_event_temp->upper_left_x = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"upper_left_y")) {
                            graphic_event_temp->upper_left_y = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"lower_right_x")) {
                            graphic_event_temp->lower_right_x = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"lower_right_y")) {
                            graphic_event_temp->lower_right_y = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"highlight_color")) {
                            graphic_event_temp->highlight_color = xmlGetProp(cur, attributes->name);
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                            graphic_event_temp->description = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }

                    graphic_event_temp->next_graphic_event = NULL;
                    if (graphic_event_head == NULL)
                        graphic_event_head = graphic_event_temp;
                    else {
                        graphic_event_p = graphic_event_head;
                        while (graphic_event_p->next_graphic_event != NULL)
                            graphic_event_p = graphic_event_p->next_graphic_event;
                        graphic_event_p->next_graphic_event = graphic_event_temp;
                    }
                    value->n_graphic_events++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'graphic_event' element\n"); }
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"rights")) {
                value->rights = loadRights(cur);
            }
            cur = cur->next;
        }
        value->graphic_event = graphic_event_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'graphic_instance' element\n"); }

    return value;
}

void loadNotationInstanceGroup(){
    xmlChar *xpath;
    xmlXPathObjectPtr result;
    xmlNodeSetPtr nodeset;
    xmlNodePtr cur;
    xmlAttr *attributes;
    xmlNodePtr temp_cur;
    
    struct notation_instance_group* notation_instance_group_temp=NULL;
    struct notation_instance_group* notation_instance_group_head=NULL;
    struct notation_instance_group* notation_instance_group_p=NULL;
    notational_layer.n_notation_instance_groups=0;
    
    xpath=(xmlChar *)"/ieee1599/notational/notation_instance_group";
    result=getNodeset(doc,xpath);
    if(!xmlXPathNodeSetIsEmpty(result->nodesetval)){
        nodeset=result->nodesetval;
        for(int i=0;i<nodeset->nodeNr;i++){//scanning notation_instance_groups
            notation_instance_group_temp=(struct notation_instance_group*)calloc(1,sizeof(struct notation_instance_group));
            cur=nodeset->nodeTab[i];
            attributes=cur->properties;

            if (notation_instance_group_temp) {
                while (attributes != NULL) {
                    if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                        notation_instance_group_temp->description = xmlGetProp(cur, attributes->name);
                    }
                    attributes = attributes->next;
                }

                //load notation_instance list
                struct notation_instance* notation_instance_temp = NULL;
                struct notation_instance* notation_instance_head = NULL;
                struct notation_instance* notation_instance_p = NULL;
                notation_instance_group_temp->n_notation_instances = 0;

                temp_cur = cur->xmlChildrenNode;
                while (temp_cur != NULL) {
                    if (!xmlStrcmp(temp_cur->name, (const xmlChar*)"notation_instance")) {
                        notation_instance_temp = (struct notation_instance*)calloc(1, sizeof(struct notation_instance));

                        notation_instance_temp = loadNotationInstance(temp_cur);

                        notation_instance_temp->next_notation_instance = NULL;
                        if (notation_instance_head == NULL)
                            notation_instance_head = notation_instance_temp;
                        else {
                            notation_instance_p = notation_instance_head;
                            while (notation_instance_p->next_notation_instance != NULL)
                                notation_instance_p = notation_instance_p->next_notation_instance;
                            notation_instance_p->next_notation_instance = notation_instance_temp;
                        }
                        notation_instance_group_temp->n_notation_instances++;
                    }
                    temp_cur = temp_cur->next;
                }
                notation_instance_group_temp->notation_instance = notation_instance_head;

                notation_instance_group_temp->next_notation_instance_group = NULL;
                if (notation_instance_group_head == NULL)
                    notation_instance_group_head = notation_instance_group_temp;
                else {
                    notation_instance_group_p = notation_instance_group_head;
                    while (notation_instance_group_p->next_notation_instance_group != NULL)
                        notation_instance_group_p = notation_instance_group_p->next_notation_instance_group;
                    notation_instance_group_p->next_notation_instance_group = notation_instance_group_temp;
                }
                notational_layer.n_notation_instance_groups++;
            }
            else { fprintf(stderr, "Memory allocation failed for 'notation_instance_group' element\n"); }
        }
    }
    notational_layer.notation_instance_group = notation_instance_group_head;
}

struct notation_instance* loadNotationInstance(xmlNodePtr cur){
    struct notation_instance* value=(struct notation_instance*)calloc(1, sizeof(struct notation_instance));;
    xmlAttr* attributes;
     
    if (value) {
        struct notation_event* notation_event_temp = NULL;
        struct notation_event* notation_event_head = NULL;
        struct notation_event* notation_event_p = NULL;
        value->n_notation_events = 0;

        value->next_notation_instance = NULL;

        attributes = cur->properties;
        while (attributes != NULL) {
            if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                value->description = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"position_in_group")) {
                value->position_in_group = xmlCharToInt(xmlGetProp(cur, attributes->name));
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"file_name")) {
                value->file_name = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"format")) {
                value->format = xmlGetProp(cur, attributes->name);
            }
            else if (!xmlStrcmp(attributes->name, (const xmlChar*)"measurement_unit")) {
                value->measurement_unit = xmlGetProp(cur, attributes->name);
            }
            attributes = attributes->next;
        }

        cur = cur->xmlChildrenNode;
        while (cur != NULL) {
            if (!xmlStrcmp(cur->name, (const xmlChar*)"notation_event")) {
                notation_event_temp = (struct notation_event*)calloc(1, sizeof(struct notation_event));

                if (notation_event_temp) {
                    attributes = cur->properties;
                    while (attributes != NULL) {
                        if (!xmlStrcmp(attributes->name, (const xmlChar*)"event_ref")) {
                            notation_event_temp->event_ref = xmlGetProp(cur, attributes->name);
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"start_position")) {
                            notation_event_temp->start_position = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"end_position")) {
                            notation_event_temp->end_position = xmlCharToDouble(xmlGetProp(cur, attributes->name));
                        }
                        else if (!xmlStrcmp(attributes->name, (const xmlChar*)"description")) {
                            notation_event_temp->description = xmlGetProp(cur, attributes->name);
                        }
                        attributes = attributes->next;
                    }

                    notation_event_temp->next_notation_event = NULL;
                    if (notation_event_head == NULL)
                        notation_event_head = notation_event_temp;
                    else {
                        notation_event_p = notation_event_head;
                        while (notation_event_p->next_notation_event != NULL)
                            notation_event_p = notation_event_p->next_notation_event;
                        notation_event_p->next_notation_event = notation_event_temp;
                    }
                    value->n_notation_events++;
                }
                else { fprintf(stderr, "Memory allocation failed for 'notation_event' element\n"); }
            }
            else if (!xmlStrcmp(cur->name, (const xmlChar*)"rights")) {
                value->rights = loadRights(cur);
            }
            cur = cur->next;
        }
        value->notation_event = notation_event_head;
    }
    else { fprintf(stderr, "Memory allocation failed for 'notation_instance' element\n"); }
    
    return value;
}

void printNotational(){

    if (notational_layer.n_graphic_insance_groups != 0 ||
        notational_layer.n_notation_instance_groups != 0 ) {

        printf("\n###Notational Layer###\n");

        printGraphicInstanceGroup();
        printNotationInstanceGroup();
    }
}

void printGraphicInstanceGroup() {
    if (notational_layer.n_graphic_insance_groups != 0) {
        printf("%i graphic instance groups\n", notational_layer.n_graphic_insance_groups);
        struct graphic_instance_group* p = notational_layer.graphic_instance_group;
        while (p) {
            printf("Graphic Instance Group ");
            if (p->description)
                printf("description=%s ",p->description);
            printf(":\n");

            if (p->n_graphic_instances != 0) {
                struct graphic_instance* k = p->graphic_instance;
                printf("    %i graphic instances\n", p->n_graphic_instances);
                int j = 0;
                while (k && j<N_DISPLAY) {
                    j++;
                    printf("    Graphic Instance: ");
                    if (k->description)
                        printf("description=%s ", k->description);
                    if (k->position_in_group)
                        printf("position_in_group=%i ", k->position_in_group);
                    if (k->file_name)
                        printf("file_name=%s ", k->file_name);
                    if (k->file_format)
                        printf("file_format=%s ", k->file_format);
                    if (k->encoding_format)
                        printf("encoding_format=%s ", k->encoding_format);
                    if (k->measurement_unit)
                        printf("measurement_unit=%s ", k->measurement_unit);
                    printf("\n");
                    if (k->n_graphic_events != 0) {
                        struct graphic_event* t = k->graphic_event;
                        int i = 0;
                        printf("        %i graphic events\n", k->n_graphic_events);
                        printf("        Graphic Events: ");
                        while (t && i < N_DISPLAY) {
                            i++;
                            printf("( ");
                            if (t->event_ref)
                                printf("event_ref=%s ", t->event_ref);
                            if (t->upper_left_x)
                                printf("upper_left_x=%.1f ", t->upper_left_x);
                            if (t->upper_left_y)
                                printf("upper_left_y=%.1f ", t->upper_left_y);
                            if (t->lower_right_x)
                                printf("lower_right_x=%.1f ", t->lower_right_x);
                            if (t->lower_right_y)
                                printf("lower_right_y=%.1f ", t->lower_right_y);
                            if (t->highlight_color)
                                printf("highlight_color=%s ", t->highlight_color);
                            if (t->description)
                                printf("description=%s ", t->description);
                            printf(") ");
                            t = t->next_graphic_event;
                        }
                        if (k->n_graphic_events > N_DISPLAY)printf("      ...");
                        printf("\n");
                    }
                    k = k->next_graphic_instance;
                }
                if (p->n_graphic_instances > N_DISPLAY)printf("    ...");
            }
            
            p = p->next_graphic_instance_group;
        }
    }
}

void printNotationInstanceGroup() {
    if (notational_layer.n_notation_instance_groups != 0) {
        printf("%i notation instance groups\n", notational_layer.n_notation_instance_groups);
        struct notation_instance_group* p = notational_layer.notation_instance_group;
        while (p) {
            printf("Notation Instance Group ");
            if (p->description)
                printf("description=%s ", p->description);
            printf(":\n");

            if (p->n_notation_instances != 0) {
                struct notation_instance* k = p->notation_instance;
                printf("    %i notation instances\n", p->n_notation_instances);
                int j = 0;
                while (k && j < N_DISPLAY) {
                    j++;
                    printf("    Notation Instance: ");
                    if (k->description)
                        printf("description=%s ", k->description);
                    if (k->position_in_group)
                        printf("position_in_group=%i ", k->position_in_group);
                    if (k->file_name)
                        printf("file_name=%s ", k->file_name);
                    if (k->format)
                        printf("format=%s ", k->format);
                    if (k->measurement_unit)
                        printf("measurement_unit=%s ", k->measurement_unit);
                    printf("\n");
                    if (k->n_notation_events != 0) {
                        struct notation_event* t = k->notation_event;
                        int i = 0;
                        printf("        %i notation events\n", k->n_notation_events);
                        printf("        Notation Events: ");
                        while (t && i < N_DISPLAY) {
                            i++;
                            printf("( ");
                            if (t->event_ref)
                                printf("event_ref=%s ", t->event_ref);
                            if (t->start_position)
                                printf("start_position=%.1f ", t->start_position);
                            if (t->end_position)
                                printf("end_position=%.1f ", t->end_position);
                            if (t->description)
                                printf("description=%s ", t->description);
                            printf(") ");
                            t = t->next_notation_event;
                        }
                        if (k->n_notation_events > N_DISPLAY)printf("        ...");
                        printf("\n");
                    }
                    k = k->next_notation_instance;
                }
                if (p->n_notation_instances > N_DISPLAY)printf("    ...");
            }

            p = p->next_notation_instance_group;
        }
    }
}

void freeGraphicEventsList(struct graphic_event* head) {
    struct graphic_event* temp;
    while (head) {
        temp = head;
        head = head->next_graphic_event;
        free(temp);
    }
}

void freeGraphicInstancesList(struct graphic_instance* head) {
    struct graphic_instance* temp;
    while (head) {
        temp = head;
        head = head->next_graphic_instance;

        if (temp->graphic_event)
            freeGraphicEventsList(temp->graphic_event);

        free(temp);
    }
}

void freeGraphicInstanceGroupsList(struct graphic_instance_group* head) {
    struct graphic_instance_group* temp;
    while (head) {
        temp = head;
        head = head->next_graphic_instance_group;

        if (temp->graphic_instance)
            freeGraphicInstancesList(temp->graphic_instance);

        free(temp);
    }
}

void freeNotationEventsList(struct notation_event* head) {
    struct notation_event* temp;
    while (head) {
        temp = head;
        head = head->next_notation_event;
        free(temp);
    }
}

void freeNotationInstancesList(struct notation_instance* head) {
    struct notation_instance* temp;
    while (head) {
        temp = head;
        head = head->next_notation_instance;

        if (temp->notation_event)
            freeNotationEventsList(temp->notation_event);

        free(temp);
    }
}

void freeNotationInstanceGroupsList(struct notation_instance_group* head) {
    struct notation_instance_group* temp;
    while (head) {
        temp = head;
        head = head->next_notation_instance_group;

        if (temp->notation_instance)
            freeNotationInstancesList(temp->notation_instance);

        free(temp);
    }
}

void freeNotationalLayer(struct notational cur) {
    if (cur.graphic_instance_group && cur.n_graphic_insance_groups)
        freeGraphicInstanceGroupsList(cur.graphic_instance_group);
    if (cur.notation_instance_group && cur.n_notation_instance_groups)
        freeNotationInstanceGroupsList(cur.notation_instance_group);
}