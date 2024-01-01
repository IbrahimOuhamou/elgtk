--بسم الله الرحمن الرحيم

local elgtk = {}

--elgtk.application 
elgtk.application = {}
elgtk.application.new = function(app_id, flags) print("alhamdo li Allah") end

--elgtk.application_window
elgtk.application_window = {}
elgtk.application_window.new = function(app) end

--elgtk.window
elgtk.window = {}
elgtk.window.new = function() end
elgtk.window.set_title = function(window, name) end
elgtk.window.set_default_size = function(window, width, height) end
elgtk.window.present = function(window) end

return elgtk

