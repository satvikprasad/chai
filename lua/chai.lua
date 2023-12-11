Chai.bg = {209, 184, 157, 255}

Chai.register_event(Chai.state, Chai.event_types.update, function()
end)

Chai.add_proc(Chai.state, "Mandelbrot Set", function()
	local vertices = {}

	for i=0,1000 do
		table.insert(vertices, {i, (i/50)^5});
	end

	return {vertices, #vertices}
end)

Chai.add_proc(Chai.state, "30 EMA", function()
	local vertices = {}

	for i=0,1000 do
		table.insert(vertices, {i/10, (i/500)^2*math.sin(i/10)});
	end

	return {vertices, #vertices}
end)

