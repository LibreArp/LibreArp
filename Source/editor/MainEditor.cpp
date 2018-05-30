//
// This file is part of LibreArp
//
// LibreArp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// LibreArp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include <sstream>
#include "../LibreArp.h"
#include "MainEditor.h"
#include "../ArpIntegrityException.h"

const int RESIZER_SIZE = 18;

MainEditor::MainEditor(LibreArp &p)
        : AudioProcessorEditor(&p),
          processor(p),
          resizer(this, &boundsConstrainer),
          tabs(TabbedButtonBar::Orientation::TabsAtTop),
          patternEditor(p),
          xmlEditor(p) {

    setSize(640, 480);

    boundsConstrainer.setMinimumSize(200, 200);

    patternEditorViewport.setViewedComponent(&patternEditor);
    tabs.addTab("Pattern", getLookAndFeel().findColour(ResizableWindow::backgroundColourId), &patternEditorViewport, false);
    tabs.addTab("XML Editor", getLookAndFeel().findColour(ResizableWindow::backgroundColourId), &xmlEditor, false);

    addAndMakeVisible(tabs);
    addAndMakeVisible(resizer, 9999);
}

MainEditor::~MainEditor() = default;

//==============================================================================
void MainEditor::paint(Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainEditor::resized() {
    tabs.setBounds(0, 0, getWidth(), getHeight());
    resizer.setBounds(getWidth() - RESIZER_SIZE, getHeight() - RESIZER_SIZE, RESIZER_SIZE, RESIZER_SIZE);
}
