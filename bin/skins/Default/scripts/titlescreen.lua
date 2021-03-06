local mposx = 0;
local mposy = 0;
local hovered = nil;
local buttonWidth = 250;
local buttonHeight = 75;
local buttonBorder = 2;
local label = -1;
gfx.GradientColors(0,128,255,255,0,128,255,0)
local gradient = gfx.LinearGradient(0,0,0,1)

view_update = function()
    if package.config:sub(1,1) == '\\' then --windows
        updateUrl, updateVersion = game.UpdateAvailable()
        os.execute("start " .. updateUrl)
    else --unix
        --TODO: Mac solution
        os.execute("xdg-open " .. updateUrl)
    end
end

mouse_clipped = function(x,y,w,h)
    return mposx > x and mposy > y and mposx < x+w and mposy < y+h;
end;

draw_button = function(name, x, y, hoverindex)
    local rx = x - (buttonWidth / 2);
    local ty = y - (buttonHeight / 2);
    gfx.BeginPath();
    gfx.FillColor(0,128,255);
    if mouse_clipped(rx,ty, buttonWidth, buttonHeight) then
       hovered = hoverindex;
       gfx.FillColor(255,128,0);
    end
    gfx.Rect(rx - buttonBorder,
        ty - buttonBorder,
        buttonWidth + (buttonBorder * 2),
        buttonHeight + (buttonBorder * 2));
    gfx.Fill();
    gfx.BeginPath();
    gfx.FillColor(40,40,40);
    gfx.Rect(rx, ty, buttonWidth, buttonHeight);
    gfx.Fill();
    gfx.BeginPath();
    gfx.FillColor(255,255,255);
    gfx.TextAlign(gfx.TEXT_ALIGN_CENTER + gfx.TEXT_ALIGN_MIDDLE);
    gfx.FontSize(40);
    gfx.Text(name, x, y);
end;

render = function(deltaTime)
    resx,resy = game.GetResolution();
    mposx,mposy = game.GetMousePos();
    gfx.Scale(resx, resy / 3)
    gfx.Rect(0,0,1,1)
    gfx.FillPaint(gradient)
    gfx.Fill()
    gfx.ResetTransform()
    gfx.BeginPath()
    buttonY = resy / 2;
    hovered = nil;
    gfx.LoadSkinFont("segoeui.ttf");
    draw_button("Start", resx / 2, buttonY, Menu.Start);
    buttonY = buttonY + 100;
    draw_button("Settings", resx / 2, buttonY, Menu.Settings);
    buttonY = buttonY + 100;
    draw_button("Exit", resx / 2, buttonY, Menu.Exit);
    gfx.BeginPath();
    gfx.FillColor(255,255,255);
    gfx.FontSize(120);
    if label == -1 then
        label = gfx.CreateLabel("unnamed_sdvx_clone", 120, 0);
    end
    gfx.TextAlign(gfx.TEXT_ALIGN_CENTER + gfx.TEXT_ALIGN_MIDDLE);
    gfx.DrawLabel(label, resx / 2, resy / 2 - 200, resx-40);
    updateUrl, updateVersion = game.UpdateAvailable()
    if updateUrl then
       gfx.BeginPath()
       gfx.TextAlign(gfx.TEXT_ALIGN_BOTTOM + gfx.TEXT_ALIGN_LEFT)
       gfx.FontSize(30)
       gfx.Text(string.format("Version %s is now available", updateVersion), 5, resy - buttonHeight - 10)
       draw_button("View", buttonWidth / 2 + 5, resy - buttonHeight / 2 - 5, view_update);
    end
end;

mouse_pressed = function(button)
    if hovered then
        hovered()
    end
    return 0
end
