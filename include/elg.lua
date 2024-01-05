--سم الله الرحمن الرحيم

local g = {}

G_APPLICATION_FLAGS_NONE = 0

g.application = {}
g.application.run = function(app, argc, argv) print("[lua] undefined g.application.run") end

g.signal = {}
g.signal.connect = function(instance, detailed_signal, function_instance, data) print("[lua] undefined g.signal.connect") end

g.object = {}
g.object.unref = function(object) print("[lua] undefined g.object.unref") end

return g

