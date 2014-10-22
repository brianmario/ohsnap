# Loaded by script/console. Land helpers here.

Pry.config.prompt = lambda do |context, nesting, pry|
  "[ohsnap] #{context}> "
end
