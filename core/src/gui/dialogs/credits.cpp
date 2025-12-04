#include <gui/dialogs/credits.h>
#include <imgui.h>
#include <gui/icons.h>
#include <gui/style.h>
#include <config.h>
#include <credits.h>
#include <version.h>
#include <gui/i18n_core.h>

namespace credits {
    ImFont* bigFont;
    ImVec2 imageSize(128.0f, 128.0f);

    void init() {
        imageSize = ImVec2(128.0f * style::uiScale, 128.0f * style::uiScale);
    }

    void show() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20.0f, 20.0f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
        ImVec2 dispSize = ImGui::GetIO().DisplaySize;
        ImVec2 center = ImVec2(dispSize.x / 2.0f, dispSize.y / 2.0f);
        ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::OpenPopup("About");
        ImGui::BeginPopupModal("About", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);

        ImGui::PushFont(style::titleFont);
        ImGui::TextUnformatted("SDR++ Community Edition");
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::Image(icons::LOGO, imageSize);
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::TextUnformatted(_("A community-driven fork welcoming all contributors and AI-enhanced development\n"));
        ImGui::TextUnformatted(_("Building upon the original SDR++ project by Alexandre Rouma (ON5RYZ)\n\n"));

        ImGui::Columns(2, "CreditColumns", true);

        ImGui::TextUnformatted(_("Community Edition Team"));
        ImGui::BulletText(_("Miguel Gomes (Project Lead)"));
        ImGui::BulletText(_("AI-Enhanced Development"));
        ImGui::BulletText(_("Community Contributors"));
        ImGui::Spacing();
        
        ImGui::TextUnformatted(_("Special Contributors"));
        ImGui::BulletText(_("PeiusMars (Parks-McClellan DSP and FFT Auto-Ranging)"));
        ImGui::BulletText(_("crackerjacques (Spiritbox Emulator)"));
        ImGui::BulletText(_("Axpelle (Discrete Recording System Feature Request)"));
        ImGui::Spacing();
        
        ImGui::TextUnformatted(_("Key Features"));
        ImGui::BulletText(_("Discrete Audio Recording System"));
        ImGui::BulletText(_("MPX Analysis for FM Broadcasting"));
        ImGui::BulletText(_("Enhanced Scanner with Frequency Manager"));
        ImGui::BulletText(_("Cross-Platform Build Improvements"));
        ImGui::BulletText(_("Community-First Development"));

        ImGui::NextColumn();
        ImGui::TextUnformatted(_("Core Libraries"));
        for (int i = 0; i < sdrpp_credits::libraryCount; i++) {
            ImGui::BulletText("%s", sdrpp_credits::libraries[i]);
        }
        ImGui::Spacing();
        
        ImGui::TextUnformatted(_("Acknowledgments"));
        ImGui::BulletText(_("Original SDR++ project and contributors"));
        ImGui::BulletText(_("Open source community"));
        ImGui::BulletText(_("Hardware and software donators"));

        ImGui::Columns(1, "CreditColumnsEnd", true);

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        
        // Always show version string
#ifndef VERSION_STR
#define VERSION_STR "dev"
#endif
        ImGui::Text(_("SDR++ CE  %s  (Built at %s, %s)"), VERSION_STR, __TIME__, __DATE__);

        ImGui::EndPopup();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
    }
}