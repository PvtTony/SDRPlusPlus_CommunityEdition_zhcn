#include <gui/style.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <config.h>
#include <utils/flog.h>
#include <filesystem>

namespace style {
    ImFont* baseFont;
    ImFont* titleFont;
    ImFont* bigFont;
    ImFont* hugeFont;
    ImVector<ImWchar> baseRanges;
    ImVector<ImWchar> titleRanges;
    ImVector<ImWchar> bigRanges;
    ImVector<ImWchar> hugeRanges;

#ifndef __ANDROID__
    float uiScale = 1.0f;
#else
    float uiScale = 3.0f;
#endif

    bool loadFonts(std::string resDir) {
        ImFontAtlas* fonts = ImGui::GetIO().Fonts;
        if (!std::filesystem::is_directory(resDir)) {
            flog::error("Invalid resource directory: {0}", resDir);
            return false;
        }

        // Chinese font path
        const std::string chineseFontPath = resDir + "/fonts/NotoSansSC-Regular.ttf";
        // Is chinese font exists
        if (!std::filesystem::exists(chineseFontPath)) {
             flog::error("Chinese font file MISSING at: {0}", chineseFontPath);
             // TODO: return false or use alternative font
        }
        // Create base font range
        ImFontGlyphRangesBuilder baseBuilder;
        baseBuilder.AddRanges(fonts->GetGlyphRangesDefault());
        baseBuilder.AddRanges(fonts->GetGlyphRangesCyrillic());
        baseBuilder.BuildRanges(&baseRanges);

        // Create title font range (full character set for titles)
        ImFontGlyphRangesBuilder titleBuilder;
        titleBuilder.AddRanges(fonts->GetGlyphRangesDefault());
        titleBuilder.AddRanges(fonts->GetGlyphRangesCyrillic());
        titleBuilder.BuildRanges(&titleRanges);

        // Create big font range
        ImFontGlyphRangesBuilder bigBuilder;
        const ImWchar bigRange[] = { '.', '9', 0 };
        bigBuilder.AddRanges(bigRange);
        bigBuilder.BuildRanges(&bigRanges);

        // Create huge font range
        ImFontGlyphRangesBuilder hugeBuilder;
        const ImWchar hugeRange[] = { 'S', 'S', 'D', 'D', 'R', 'R', '+', '+', ' ', ' ', 0 };
        hugeBuilder.AddRanges(hugeRange);
        hugeBuilder.BuildRanges(&hugeRanges);

        // Chinese font range
        const ImWchar* chineseRanges = fonts->GetGlyphRangesChineseFull();

        // Merge config
        ImFontConfig mergeConfig;
        mergeConfig.MergeMode = true;
        mergeConfig.PixelSnapH = true; // Make font looks better

        // Add bigger fonts for frequency select and title
        baseFont = fonts->AddFontFromFileTTF(((std::string)(resDir + "/fonts/Roboto-Medium.ttf")).c_str(), 16.0f * uiScale, NULL, baseRanges.Data);
        // Load chinese font
        fonts->AddFontFromFileTTF(chineseFontPath.c_str(), 16.0f * uiScale, &mergeConfig, chineseRanges);
        if (baseFont == nullptr) flog::error("Failed to load Base English font");

        // Check chinese font is loaded successfully
        ImFont* baseChineseFont = fonts->AddFontFromFileTTF(chineseFontPath.c_str(), 16.0f * uiScale, &mergeConfig, chineseRanges);
        if (baseChineseFont == nullptr) {
            flog::error("Failed to load Chinese font for Base! Likely OTF format issue or file corrupt.");
            // TODO: fallback plan
            // fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 16.0f * uiScale, &mergeConfig, chineseRanges);
        }
        titleFont = fonts->AddFontFromFileTTF(((std::string)(resDir + "/fonts/Roboto-Medium.ttf")).c_str(), 32.0f * uiScale, NULL, titleRanges.Data);
        if (titleFont != nullptr) {
            ImFont* titleChineseFont = fonts->AddFontFromFileTTF(chineseFontPath.c_str(), 32.0f * uiScale, &mergeConfig, chineseRanges);
            if (titleChineseFont == nullptr) flog::error("Failed to load Chinese font for Title!");
        }

        bigFont = fonts->AddFontFromFileTTF(((std::string)(resDir + "/fonts/Roboto-Medium.ttf")).c_str(), 45.0f * uiScale, NULL, bigRanges.Data);
        hugeFont = fonts->AddFontFromFileTTF(((std::string)(resDir + "/fonts/Roboto-Medium.ttf")).c_str(), 128.0f * uiScale, NULL, hugeRanges.Data);

        return true;
    }

    void beginDisabled() {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        auto& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;
        ImVec4 btnCol = colors[ImGuiCol_Button];
        ImVec4 frameCol = colors[ImGuiCol_FrameBg];
        ImVec4 textCol = colors[ImGuiCol_Text];
        btnCol.w = 0.15f;
        frameCol.w = 0.30f;
        textCol.w = 0.65f;
        ImGui::PushStyleColor(ImGuiCol_Button, btnCol);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, frameCol);
        ImGui::PushStyleColor(ImGuiCol_Text, textCol);
    }

    void endDisabled() {
        ImGui::PopItemFlag();
        ImGui::PopStyleColor(3);
    }
}

namespace ImGui {
    void LeftLabel(const char* text) {
        float vpos = ImGui::GetCursorPosY();
        ImGui::SetCursorPosY(vpos + GImGui->Style.FramePadding.y);
        ImGui::TextUnformatted(text);
        ImGui::SameLine();
        ImGui::SetCursorPosY(vpos);
    }

    void FillWidth() {
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    }
}
