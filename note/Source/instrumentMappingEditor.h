/*
  ==============================================================================

    instrumentMappingEditor.h
    Created: 11 May 2014 11:32:11am
    Author:  patrick

  ==============================================================================
*/

#ifndef INSTRUMENTMAPPINGEDITOR_H_INCLUDED
#define INSTRUMENTMAPPINGEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class instrumentMappingEditor : public Viewport
{
public:
    class mappingEditorGraph;
    
    instrumentMappingEditor(const String& componentName, Component* Parent);
    ~instrumentMappingEditor();
private:
    ScopedPointer<Component> parent;
    ScopedPointer<mappingEditorGraph> graph;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (instrumentMappingEditor)
};
    
class instrumentMappingEditor::mappingEditorGraph : 
public Component, public FileDragAndDropTarget, public ButtonListener
{
public:
    float width;
    float height;
    int num_columns;
    
    class Zone;
    
    mappingEditorGraph();
    ~mappingEditorGraph();
    
    void paint(Graphics& g);
    void buttonClicked(Button* button);
    
    void mouseDrag(const MouseEvent& event);
    void mouseUp(const MouseEvent& event);
    void mouseDown(const MouseEvent& event);
    
    void filesDropped(const StringArray& files, int x, int y);
    bool isInterestedInFileDrag(const StringArray& files){return true;};
    
    Array<Zone*> zones;
    ScopedPointer<LassoComponent<Zone*> > lasso;
    
    template <class SelectableItemType>
    class Lasso_Source : public LassoSource<SelectableItemType>, public ChangeListener
    {
    public:
        ~Lasso_Source() {set = nullptr;};
        Array<Zone*> zones;
        SelectedItemSet<SelectableItemType>* set;
        
        void findLassoItemsInArea (Array <SelectableItemType>& itemsFound,
                                       const Rectangle<int>& area){
            itemsFound.add(zones[0]);
            std::cout<<itemsFound.size()<<std::endl;
        };
        SelectedItemSet<SelectableItemType>& getLassoSelection(){
            set = new SelectedItemSet<SelectableItemType>;
            set->addChangeListener(this);
            //set->selectOnly(zones[0]);
            return *set;
        };
        
        void changeListenerCallback(ChangeBroadcaster* source){
            std::cout<<"changed!"<<std::endl;
            if (source = set){
                std::cout<<source->begin()->x;
            }
        };
    };

    
    Lasso_Source<Zone*> lasso_source;
private:
    Zone* dragged_zone;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (mappingEditorGraph)
};

class instrumentMappingEditor::mappingEditorGraph::Zone : public TextButton
{
public:
    const String name;
    int x;
    int y;
    int height;
    instrumentMappingEditor::mappingEditorGraph* parent;
    
    void register_parent(instrumentMappingEditor::mappingEditorGraph* parent);
    void mouseDown(const MouseEvent& event);

    Zone(const String& sample_name) : TextButton(""), name(sample_name){};
    
private:
    
};



#endif  // INSTRUMENTMAPPINGEDITOR_H_INCLUDED
