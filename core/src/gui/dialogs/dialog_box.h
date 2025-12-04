#pragma once
#include "dialog_box.h"
#include <imgui.h>
#include <string>
#include <gui/gui.h>
#include <gui/i18n_core.h>

#define GENERIC_DIALOG_BUTTONS_OK           (std::string(_("Ok")) + '\0')
#define GENERIC_DIALOG_BUTTONS_YES_NO       (std::string(_("Yes")) + '\0' + _("No") + '\0')
#define GENERIC_DIALOG_BUTTONS_APPLY_CANCEL (std::string(_("Apply")) + '\0' + _("Cancel") + '\0')
#define GENERIC_DIALOG_BUTTONS_OK_CANCEL    (std::string(_("Ok")) + '\0' + _("Cancel") + '\0')

#define GENERIC_DIALOG_BUTTON_OK    0
#define GENERIC_DIALOG_BUTTON_YES   0
#define GENERIC_DIALOG_BUTTON_NO    1
#define GENERIC_DIALOG_BUTTON_APPLY 0
#define GENERIC_DIALOG_BUTTON_CANCE 1

namespace ImGui {
    template <typename Func>
    int GenericDialog(const char* id, bool& open, const char* buttons, Func draw) {
        // If not open, return
        if (!open) { return -1; }

        // Draw popup
        gui::mainWindow.lockWaterfallControls = true;
        std::string idstr = std::string("##") + std::string(id);
        ImGui::OpenPopup(id);
        if (ImGui::BeginPopup(id, ImGuiWindowFlags_NoResize)) {
            // Draw widgets
            draw();

            // Draw buttons
            int bid = 0;
            while (buttons[0]) {
                int len = strlen(buttons);

                // Draw button
                if (bid) { ImGui::SameLine(); }
                if (ImGui::Button((buttons + idstr).c_str())) {
                    open = false;
                    ImGui::EndPopup();
                    return bid;
                }

                buttons += len + 1;
                bid++;
            }

            ImGui::EndPopup();
        }

        return -1;
    }
}