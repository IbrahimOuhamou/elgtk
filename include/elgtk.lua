--بسم الله الرحمن الرحيم

local elgtk = {}
g = require("include.elg")
--elgtk.widget
elgtk.widget = {}
elgtk.widget.show = function(widget) print("[lua] undefined elgtk.widget.show") end


--elgtk.application 
elgtk.application = {}
elgtk.application.new = function(app_id, flags) print("[lua] undefined elgtk.application.new") end

--elgtk.application_window
elgtk.application_window = {}
elgtk.application_window.new = function(app) print("[lua] undefined elgtk.application_window.new") end

--elgtk.window
elgtk.window = {}
elgtk.window.new = function() print("[lua] undefined elgtk.window.new") end
elgtk.window.set_title = function(window, name) print("[lua] undefined elgtk.window.set_title") end
elgtk.window.set_default_size = function(window, width, height) print("[lua] undefined elgtk.window.set_default_size") end
elgtk.window.present = function(window) print("[lua] undefined elgtk.window.present") end

return elgtk

