local C = Chai

C.bg = {55, 55, 55, 255}

C.procedures.add(C.state, "Mandelbrot Set", function()
	local vertices = {}

	for i=0,1000 do
		table.insert(vertices, {i, (i/50)^5});
	end

	return {vertices, #vertices}
end)

