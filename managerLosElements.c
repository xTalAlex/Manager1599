/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "managerLosElements.h"

ornament loadOrnamentValue(xmlNodePtr cur){
    ornament value;
    
    return value;
}

horizontal_symbol loadHorizontalSymbolValue(xmlNodePtr cur){
    horizontal_symbol value;
    xmlAttr *attributes;
    xmlNodePtr temp_cur;
    
    if(!xmlStrcmp(cur->name,(const xmlChar*)"arpeggio")){       
        struct notehead_ref* notehead_ref_temp=NULL;
        struct notehead_ref* notehead_ref_head=NULL;
        struct notehead_ref* notehead_ref_p=NULL;
        
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"shape")){
                value.arpeggio.shape=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"direction")){
                value.arpeggio.direction=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){//notehead_ref list in arpeggio
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"notehead_ref")){
                notehead_ref_temp=(struct notehead_ref*)malloc(sizeof(struct notehead_ref));
                notehead_ref_temp=calloc(1,sizeof(struct notehead_ref));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"spine_ref")){
                        //notehead_ref_temp->spine_ref=xmlGetPropr(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                notehead_ref_temp->next_notehead_ref=NULL;
                if(notehead_ref_head==NULL)
                    notehead_ref_head=notehead_ref_temp;
                else{
                    notehead_ref_p=notehead_ref_head;
                    while(notehead_ref_p->next_notehead_ref!=NULL)
                        notehead_ref_p=notehead_ref_p->next_notehead_ref;
                    notehead_ref_p=notehead_ref_temp;
                }
            }  
        }//end notehead_ref list in arpeggio
        value.arpeggio.notehead_ref=notehead_ref_head;
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"bend")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.bend.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                //value.bend.spine_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.bend.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"to_pitch")){
                value.bend.to_pitch=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"to_accidental")){
                //value.bend.to_accidentale=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"to_octave")){
                value.bend.to_octave=xmlCharToInt(xmlGetProp(cur,attributes->name));
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"breath_mark")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.breath_mark.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.breath_mark.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
                //value.breath_mark.staff_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_start_end_ref")){
                //value.breath_mark.spine_start_end_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"chord_symbol")){
        value.chord_symbol.chord_symbol_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.chord_symbol.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                //value.chord_symbol.spine_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"dynamic")){
        value.dynamic.dynamic_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.dynamic.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"extension_line_to")){
                value.dynamic.extension_line_to=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"extension_line_shape")){
                value.dynamic.extension_line_shape=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
                value.dynamic.staff_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                value.dynamic.event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"fermata")){
        value.fermata.fermata_value=xmlCharToInt(xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.fermata.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                //value.fermata.spine_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"glissando")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.glissando.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                //value.glissando.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                //value.glissando.end_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"hairpin")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.hairpin.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.hairpin.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
                //value.hairpin.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_end_event_ref")){
                //value.hairpin.start_end_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"octave_bracket")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.octave_bracket.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.octave_bracket.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
                //value.octave_bracket.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_end_event_ref")){
                //value.octave_bracket.start_end_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"pedal_start")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.pedal_start.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                //value.pedal_start.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"pedal_end")){
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.pedal_end.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                //value.pedal_end.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"percussion_beater")){
        value.percussion_beater.percussion_beater_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.percussion_beater.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.percussion_beater.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                //value.percussion_beater.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                //value.percussion_beater.end_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"percussion_special")){
        value.percussion_special.percussion_special_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.percussion_special.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"type")){
                value.percussion_special.type=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                //value.percussion_special.spine_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"slur")){
        //load svg
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.slur.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_start_end_ref")){
                //value.slur.spine_start_end_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"shape")){
                value.slur.shape=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"bracketed")){
                value.slur.bracketed=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"special_beam")){
        struct notehead_ref* notehead_ref_temp=NULL;
        struct notehead_ref* notehead_ref_head=NULL;
        struct notehead_ref* notehead_ref_p=NULL;
        
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.special_beam.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"fanned_from")){
                value.special_beam.fanned_from=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"fanned_to")){
                value.special_beam.fanned_to=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){//notehead_ref list in special_beam
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"notehead_ref")){
                notehead_ref_temp=(struct notehead_ref*)malloc(sizeof(struct notehead_ref));
                notehead_ref_temp=calloc(1,sizeof(struct notehead_ref));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"spine_ref")){
                        //notehead_ref_temp->spine_ref=xmlGetPropr(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                notehead_ref_temp->next_notehead_ref=NULL;
                if(notehead_ref_head==NULL)
                    notehead_ref_head=notehead_ref_temp;
                else{
                    notehead_ref_p=notehead_ref_head;
                    while(notehead_ref_p->next_notehead_ref!=NULL)
                        notehead_ref_p=notehead_ref_p->next_notehead_ref;
                    notehead_ref_p=notehead_ref_temp;
                }
            }  
        }//end notehead_ref list in special_beam
        value.special_beam.notehead_ref=notehead_ref_head;
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"tablature_hsymbol")){
        struct tablature_element* tablature_element_temp=NULL;
        struct tablature_element* tablature_element_head=NULL;
        struct tablature_element* tablature_element_p=NULL;
        
        struct barre* barre_temp=NULL;
        struct barre* barre_head=NULL;
        struct barre* barre_p=NULL;
        
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.tablature_hsymbol.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                //value.tablature_hsymbol.spine_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"string_number")){
                value.tablature_hsymbol.string_number=xmlCharToInt(xmlGetProp(cur,attributes->name));
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_fret")){
                value.tablature_hsymbol.start_fret=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"fret_number")){
                value.tablature_hsymbol.fret_number=xmlCharToInt(xmlGetProp(cur,attributes->name));
            }
            attributes=attributes->next;
        }
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tablature_element")){
                tablature_element_temp=(struct tablature_element*)malloc(sizeof(struct tablature_element));
                tablature_element_temp=calloc(1,sizeof(struct tablature_element));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"shape")){
                        tablature_element_temp->shape=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"string_position")){
                        tablature_element_temp->string_position=xmlGetProp(temp_cur,attributes->name);
                    }
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"fret_position")){
                        tablature_element_temp->fret_position=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                tablature_element_temp->next_tablature_element=NULL;
                if(tablature_element_head==NULL)
                    tablature_element_head=tablature_element_temp;
                else{
                    tablature_element_p=tablature_element_head;
                    while(tablature_element_p->next_tablature_element!=NULL)
                        tablature_element_p=tablature_element_p->next_tablature_element;
                    tablature_element_p=tablature_element_temp;
                }
            }  
            else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"barre")){
                barre_temp=(struct barre*)malloc(sizeof(struct barre));
                barre_temp=calloc(1,sizeof(struct barre));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"start_string_position")){
                        barre_temp->start_string_position=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"end_string_position")){
                        barre_temp->end_string_position=xmlGetProp(temp_cur,attributes->name);
                    }
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"fret_position")){
                        barre_temp->fret_position=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                barre_temp->next_barre=NULL;
                if(barre_head==NULL)
                    barre_head=barre_temp;
                else{
                    barre_p=barre_head;
                    while(barre_p->next_barre!=NULL)
                        barre_p=barre_p->next_barre;
                    barre_p=barre_temp;
                }
            }   
        }
        value.tablature_hsymbol.tablature_elements=tablature_element_head;
        value.tablature_hsymbol.barres=barre_head;
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"repeat")){
        struct jump_to* jump_to_temp=NULL;
        struct jump_to* jump_to_head=NULL;
        struct jump_to* jump_to_p=NULL;
        
        struct end* end_temp=NULL;
        struct end* end_head=NULL;
        struct end* end_p=NULL;
        
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.repeat.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                //value.repeat.spine_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"repeat_text")){
                value.repeat.repeat_text=xmlNodeListGetString(doc,temp_cur->xmlChildrenNode,1);
            }  
            else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"jump_to")){
                jump_to_temp=(struct jump_to*)malloc(sizeof(struct jump_to));
                jump_to_temp=calloc(1,sizeof(struct jump_to));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"id")){
                        jump_to_temp->id=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"spine_ref")){
                        //jump_to_temp->spine_ref=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                jump_to_temp->next_jump_to=NULL;
                if(jump_to_head==NULL)
                    jump_to_head=jump_to_temp;
                else{
                    jump_to_p=jump_to_head;
                    while(jump_to_p->next_jump_to!=NULL)
                        jump_to_p=jump_to_p->next_jump_to;
                    jump_to_p=jump_to_temp;
                }
            } 
            else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"end")){
                end_temp=(struct end*)malloc(sizeof(struct end));
                end_temp=calloc(1,sizeof(struct end));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"id")){
                        end_temp->id=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"spine_ref")){
                        //end_temp->spine_ref=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                end_temp->next_end=NULL;
                if(end_head==NULL)
                    end_head=end_temp;
                else{
                    end_p=end_head;
                    while(end_p->next_end!=NULL)
                        end_p=end_p->next_end;
                    end_p=end_temp;
                }
            }   
        }
        value.repeat.jump_tos=jump_to_head;
        value.repeat.ends=end_head;
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"segno")){
        value.segno.segno_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.segno.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                //value.segno.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"coda")){
        value.coda.coda_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.coda.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                //value.coda.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"fine")){
        value.fine.fine_value=xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.fine.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                //value.fine.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        } 
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"multiple_endings")){
        struct multiple_ending* multiple_ending_temp=NULL;
        struct multiple_ending* multiple_ending_head=NULL;
        struct multiple_ending* multiple_ending_p=NULL;
        
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.multiple_endings.id=xmlGetProp(cur,attributes->name);
            }
            attributes=attributes->next;
        }
        temp_cur=cur->xmlChildrenNode;
        while(temp_cur!=NULL){
            if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"multiple_ending")){
                multiple_ending_temp=(struct multiple_ending*)malloc(sizeof(struct multiple_ending));
                multiple_ending_temp=calloc(1,sizeof(struct multiple_ending));
                attributes=temp_cur->properties;
                while(attributes!=NULL){
                    if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"id")){
                        multiple_ending_temp->id=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"number")){
                        multiple_ending_temp->number=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"spine_start_end_ref")){
                        //multiple_ending_temp->spine_start_end_ref=xmlGetProp(temp_cur,attributes->name);
                    }
                    else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"return_to")){
                        //multiple_ending_temp->return_to=xmlGetProp(temp_cur,attributes->name);
                    }
                    attributes=attributes->next;
                }
                multiple_ending_temp->next_multiple_ending=NULL;
                if(multiple_ending_head==NULL)
                    multiple_ending_head=multiple_ending_temp;
                else{
                    multiple_ending_p=multiple_ending_head;
                    while(multiple_ending_p->next_multiple_ending!=NULL)
                        multiple_ending_p=multiple_ending_p->next_multiple_ending;
                    multiple_ending_p=multiple_ending_temp;
                }
            }  
        }
        value.multiple_endings.multiple_ending=multiple_ending_head;
    }
    else if(!xmlStrcmp(cur->name,(const xmlChar*)"custom_hsymbol")){
        //load svg
        attributes=cur->properties;
        while(attributes!=NULL){
            if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                value.custom_hsymbol.id=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"start_event_ref")){
                //value.custom_hsymbol.start_event_ref=xmlGetProp(cur,attributes->name);
            }
            else if(!xmlStrcmp(attributes->name,(const xmlChar*)"end_event_ref")){
                //value.custom_hsymbol.end_event_ref=xmlGetProp(cur,attributes->name);
            }

            attributes=attributes->next;
        }
    }
    else
        fprintf(stderr,"Element is not an Horizontal Symbol\n");
    
    return value;
}

struct voice_item* loadVoiceItemValue(xmlNodePtr cur){   
    xmlAttr* attributes;
    struct voice_item* value=(struct voice_item*)malloc(sizeof(struct voice_item));
    value=calloc(1,sizeof(struct voice_item));
    
    value->next_voice_item=NULL;
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
            //value.staff_ref=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"notation_style")){
            value->notation_style=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    
    return value;
}

struct measure* loadMeasureValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct measure* value=(struct measure*)malloc(sizeof(struct measure));
    value=calloc(1,sizeof(struct measure));
    
    struct voice* voice_temp=NULL;
    struct voice* voice_head=NULL;
    struct voice* voice_p=NULL;
    value->n_voices=0; 
    
    value->next_measure=NULL;
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"number")){
            value->number=xmlCharToInt(xmlGetProp(cur,attributes->name));
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"show_number")){
            value->show_number=xmlGetProp(cur,attributes->name);
        }  
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"numbering_style")){
            value->numbering_style=xmlGetProp(cur,attributes->name);
        }     
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"voice")){
            voice_temp=(struct voice*)malloc(sizeof(struct voice));
            voice_temp=calloc(1,sizeof(struct voice*));
            voice_temp=loadVoiceValue(temp_cur);
            voice_temp->next_voice=NULL;
            if(voice_head==NULL){
                voice_head=voice_temp;
            }
            else{
                voice_p=voice_head;
                while(voice_p->next_voice!=NULL)
                    voice_p=voice_p->next_voice;
                voice_p->next_voice=voice_temp;
            }
            value->n_voices++;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"multiple_rest")){
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"number_of_measures")){
                    value->multiple_rest.number_of_measures=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                    //value->multiple_rest.event_ref=xmlGetPropr(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }  
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"measure_repeat")){
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"number_of_measures")){
                    value->measure_repeat.number_of_measures=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"event_ref")){
                    //value->measure_repeat.event_ref=xmlGetPropr(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }
        }
    }
    value->voices=voice_head;
    
    return value;
}

struct clef* loadCleffValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct clef* value;
    return value;
}

struct key_signature* loadKeySignatureValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct key_signature* value;
    return value;
}

struct custom_key_signature* loadCustomKeySignatureValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct custom_key_signature* value;
    return value;
}

struct time_signature* loadTimeSignatureValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct time_signature* value;
    return value;
}

struct barline* loadBarlineValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct barline* value;
    return value;
}

struct tablature_tuning* loadTablatureTuningValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct tablature_tuning* value;
    return value;
}

struct voice* loadVoiceValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct voice* value=(struct voice*)malloc(sizeof(struct voice));
    value=calloc(1,sizeof(struct voice));    
    
    struct chord* chord_temp=NULL;
    struct chord* chord_head=NULL;
    struct chord* chord_p=NULL;
    value->n_chords=0;
    
    struct rest* rest_temp=NULL;
    struct rest* rest_head=NULL;
    struct rest* rest_p=NULL;
    value->n_rests=0;
    
    struct tablature_symbol* tablature_symbol_temp=NULL;
    struct tablature_symbol* tablature_symbol_head=NULL;
    struct tablature_symbol* tablature_symbol_p=NULL;
    value->n_tablature_symbols=0;
    
    struct gregorian_symbol* gregorian_symbol_temp=NULL;
    struct gregorian_symbol* gregorian_symbol_head=NULL;
    struct gregorian_symbol* gregorian_symbol_p=NULL;
    value->n_gregorian_symbols=0;
    
    value->next_voice=NULL;
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"voice_item_ref")){
            //value->voice_item_ref=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(cur->name,(const xmlChar*)"ossia")){
            value->ossia=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"chord")){
            chord_temp=(struct chord*)malloc(sizeof(struct chord));
            chord_temp=calloc(1,sizeof(struct chord*));
            chord_temp=loadChordValue(temp_cur);
            chord_temp->next_chord=NULL;
            if(chord_head==NULL){
                chord_head=chord_temp;
            }
            else{
                chord_p=chord_head;
                while(chord_p->next_chord!=NULL)
                    chord_p=chord_p->next_chord;
                chord_p->next_chord=chord_temp;
            }
            value->n_chords++;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"rest")){
            rest_temp=(struct rest*)malloc(sizeof(struct rest));
            rest_temp=calloc(1,sizeof(struct rest*));
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                    rest_temp->id=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                    //rest_temp->spine_ref=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
                    //rest_temp->staff_ref=xmlGetProp(temp_cur,attributes->name);

                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"hidden")){
                    rest_temp->hidden=xmlGetProp(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }
            if(temp_cur->xmlChildrenNode!=NULL){
                temp_cur=temp_cur->xmlChildrenNode;
                if(temp_cur!=NULL){
                    do{
                        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"duration")){
                           rest_temp->duration=loadDurationValue(temp_cur);
                        }
                        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"augmentation_dots")){
                           rest_temp->augmentation_dots=(struct augmentation_dots){1};
                           if(xmlGetProp(temp_cur,(const xmlChar*)"number")!=NULL)
                            rest_temp->augmentation_dots=(struct augmentation_dots){ xmlCharToInt(xmlGetProp(temp_cur,(const xmlChar*)"augmentation_dots"))};
                        }
                        temp_cur=temp_cur->next;
                    }while(temp_cur->next!=NULL);
                }
                temp_cur=temp_cur->parent;
            }
            rest_temp->next_rest=NULL;
            if(rest_head==NULL){
                rest_head=rest_temp;
            }
            else{
                rest_p=rest_head;
                while(rest_p->next_rest!=NULL)
                    rest_p=rest_p->next_rest;
                rest_p->next_rest=rest_temp;
            }
            value->n_rests++;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tablature_symbol")){
            tablature_symbol_temp=(struct tablature_symbol*)malloc(sizeof(struct tablature_symbol));
            tablature_symbol_temp=calloc(1,sizeof(struct tablature_symbol*));
            
            struct key* key_temp=NULL;
            struct key* key_head=NULL;
            struct key* key_p=NULL;
            tablature_symbol_temp->n_keys=0;
            
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"id")){
                    tablature_symbol_temp->id=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"spine_ref")){
                    //tablature_symbol_temp->spine_ref=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"stem_direction")){
                    tablature_symbol_temp->stem_direction=xmlGetProp(temp_cur,attributes->name);

                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"beam_before")){
                    tablature_symbol_temp->beam_before=xmlGetProp(temp_cur,attributes->name);
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"beam_after")){
                    tablature_symbol_temp->beam_after=xmlGetProp(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }
            if(temp_cur->xmlChildrenNode!=NULL){
                temp_cur=temp_cur->xmlChildrenNode;
                if(temp_cur!=NULL){
                    do{
                        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"duration")){
                           tablature_symbol_temp->duration=loadDurationValue(temp_cur);
                        }
                        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"augmentation_dots")){
                           tablature_symbol_temp->augmentation_dots=(struct augmentation_dots){1};
                           if(xmlGetProp(temp_cur,(const xmlChar*)"number")!=NULL)
                            tablature_symbol_temp->augmentation_dots=(struct augmentation_dots){ xmlCharToInt(xmlGetProp(temp_cur,(const xmlChar*)"augmentation_dots"))};
                        }
                        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"key")){
                            key_temp=loadKeyValue(temp_cur);
                            key_temp->next_key=NULL;
                            if(key_head==NULL){
                                key_head=key_temp;
                            }
                            else{
                                key_p=key_head;
                                while(key_p->next_key!=NULL)
                                    key_p=key_p->next_key;
                                key_p->next_key=key_temp;
                            }
                            tablature_symbol_temp->n_keys++;
                        }
                        temp_cur=temp_cur->next;
                    }while(temp_cur->next!=NULL);
                }
                temp_cur=temp_cur->parent;
            }
            tablature_symbol_temp->keys=key_head;
            tablature_symbol_temp->next_tablature_symbol=NULL;
            if(tablature_symbol_head==NULL){
                tablature_symbol_head=tablature_symbol_temp;
            }
            else{
                tablature_symbol_p=tablature_symbol_head;
                while(tablature_symbol_p->next_tablature_symbol!=NULL)
                    tablature_symbol_p=tablature_symbol_p->next_tablature_symbol;
                tablature_symbol_p->next_tablature_symbol=tablature_symbol_temp;
            }
            value->n_tablature_symbols++;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"gregorian_symbol")){
            gregorian_symbol_temp=(struct gregorian_symbol*)malloc(sizeof(struct gregorian_symbol));
            gregorian_symbol_temp=calloc(1,sizeof(struct gregorian_symbol*));
            
            struct notehead* notehead_temp=NULL;
            struct notehead* notehead_head=NULL;
            struct notehead* notehead_p=NULL;
            gregorian_symbol_temp->n_noteheads=0;
            
            attributes=cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(cur->name,(const xmlChar*)"id")){
                    gregorian_symbol_temp->id=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"neume")){
                    gregorian_symbol_temp->neume=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"inflexion")){
                    gregorian_symbol_temp->inflexion=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"subpunctis")){
                    gregorian_symbol_temp->subpunctis=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"interpretative_mark")){
                    gregorian_symbol_temp->interpretative_mark=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"mora")){
                    gregorian_symbol_temp->mora=xmlGetProp(cur,attributes->name);
                }
                else if(!xmlStrcmp(cur->name,(const xmlChar*)"spine_ref")){
                    //gregorian_symbol_temp->spine_ref=xmlGetProp(cur,attributes->name);
                }           
                attributes=attributes->next;
            }
            if(temp_cur->xmlChildrenNode!=NULL){
                temp_cur=temp_cur->xmlChildrenNode;
                if(temp_cur!=NULL){
                    do{
                        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"notehead")){
                            notehead_temp=loadNoteheadValue(temp_cur);
                            notehead_temp->next_notehead=NULL;
                            if(notehead_head==NULL){
                                notehead_head=notehead_temp;
                            }
                            else{
                                notehead_p=notehead_head;
                                while(notehead_p->next_notehead!=NULL)
                                    notehead_p=notehead_p->next_notehead;
                                notehead_p->next_notehead=notehead_temp;
                            }
                            gregorian_symbol_temp->n_noteheads++;
                        }
                        temp_cur=temp_cur->next;
                    }while(temp_cur->next!=NULL);
                }
                temp_cur=temp_cur->parent;
            }
            gregorian_symbol_temp->notehead=notehead_head;
            gregorian_symbol_temp->next_gregorian_symbol=NULL;
            if(gregorian_symbol_head==NULL){
                gregorian_symbol_head=gregorian_symbol_temp;
            }
            else{
                gregorian_symbol_p=gregorian_symbol_head;
                while(gregorian_symbol_p->next_gregorian_symbol!=NULL)
                    gregorian_symbol_p=gregorian_symbol_p->next_gregorian_symbol;
                gregorian_symbol_p->next_gregorian_symbol=gregorian_symbol_temp;
            }
            value->n_gregorian_symbols++;
        }
        temp_cur=temp_cur->next;
    }
    value->chords=chord_head;
    value->rests=rest_head;
    value->tablature_symbols=tablature_symbol_head;
    value->gregorian_symbols=gregorian_symbol_head;
    
    return value;
}

struct chord* loadChordValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct chord* value=(struct chord*)malloc(sizeof(struct chord));
    value=calloc(1,sizeof(struct chord));
    
    return value;  
}

struct notehead* loadNoteheadValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct notehead* value=(struct notehead*)malloc(sizeof(struct notehead));
    value=calloc(1,sizeof(struct notehead));
    
    return value;    
}

struct duration loadDurationValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct duration* value=(struct duration*)malloc(sizeof(struct duration));
    value=calloc(1,sizeof(struct duration));
    
    return *value;     
}

struct key* loadKeyValue(xmlNodePtr cur){
    xmlAttr* attributes;
    xmlNodePtr temp_cur;
    struct key* value=(struct key*)malloc(sizeof(struct key));
    value=calloc(1,sizeof(struct key));
    value->tie=0;
    
    attributes=cur->properties;
    while(attributes!=NULL){
        if(!xmlStrcmp(attributes->name,(const xmlChar*)"ïd")){
            value->id=xmlGetProp(cur,attributes->name);
        }
        else if(!xmlStrcmp(attributes->name,(const xmlChar*)"staff_ref")){
            //value->staff_ref=xmlGetProp(cur,attributes->name);
        }
        attributes=attributes->next;
    }
    temp_cur=cur->xmlChildrenNode;
    while(temp_cur!=NULL){
        if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tablature_pitch")){
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"string_number")){
                    value->tablature_pitch.string_number=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                else if(!xmlStrcmp(attributes->name,(const xmlChar*)"key_number")){
                    value->tablature_pitch.key_number=xmlCharToInt(xmlGetProp(temp_cur,attributes->name));
                }
                attributes=attributes->next;
            }
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tablature_articulation")){
            attributes=temp_cur->properties;
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"shape")){
                    value->tablature_articulation.shape=xmlGetProp(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }        
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tie")){
            value->tie=1;
        }
        else if(!xmlStrcmp(temp_cur->name,(const xmlChar*)"tablature_fingering")){
            attributes=temp_cur->properties;
            value->tablature_fingering.tablature_fingering_value=xmlNodeListGetString(doc,temp_cur->xmlChildrenNode,1);
            while(attributes!=NULL){
                if(!xmlStrcmp(attributes->name,(const xmlChar*)"shape")){
                    value->tablature_fingering.shape=xmlGetProp(temp_cur,attributes->name);
                }
                attributes=attributes->next;
            }          
        }
        temp_cur=temp_cur->next;
    }
    
    
    return value;  
}