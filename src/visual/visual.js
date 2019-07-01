// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   visual.js                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2019/06/26 14:46:10 by bwan-nan          #+#    #+#             //
//   Updated: 2019/07/01 00:20:42 by bwan-nan         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

var     cy;
var     data;
var     moves;
var     origins;
var     tunnels = [];
var     tunnel;
var     from = [];
var     k = 0;
var     ants_out = 0;
var     time; 
var     pause = false;

$(document).ready(function() {
    $.getJSON("data.json", function(json) {
        data = json;
		cy = cytoscape({
			container: $("#cy"),
			elements: data,
			layout: {
			name: 'cose-bilkent',
			animate: false,
			randomize: true
			},
			style: [
				{
					selector: 'node',
					style: {
						'background-color': 'white',
						'label': 'data(id)',
                        'color': 'black'
					}
				},

				{
					selector: 'edge',
					style: {
						'width': 3,
						'line-color': 'white'
					}
				}
			],
		});
        cy.elements('node[flag = 0]').style('background-color', 'green');
        cy.elements('node[flag = 1]').style('background-color', 'red'); 
        moves = copyObject(Object.values(data.moves));
        origins = [cy.nodes('node[flag = 0]').id()];
        $("#ant_qty").text(data.ant_qty);
        $("#node_qty").text(data.nodes.length);
        $("#edge_qty").text(data.edges.length);
        $("#path_qty").text(data.paths.length);
        $("#rounds").text(k);
        $("#out").text(ants_out);
		document.getElementById("layoutButton").addEventListener("click", function(){
            var layout = cy.layout({
                name: 'cose-bilkent',
          		animate: 'end',
				animationEasing: 'ease-out',
           	    animationDuration: 1000,
				randomize: true
         	});
          	layout.run();
        });
		document.getElementById("randomize").addEventListener("click", function(){
			var layout = cy.layout({
				name: 'random',
				animate: true,
				animationDuration: 1000,
				animationEasing: 'ease-out'
			});
		    layout.run();
		});


        $("#reset").click(function() {
            k = 0;
            ants_out = 0;
            origins = [cy.nodes('node[flag = 0]').id()];
            $("#rounds").text(k);
            $("#out").text(ants_out);
            moves = copyObject(Object.values(data.moves));
            cy.elements('node').forEach(function(node) {
                if (node.id() != cy.nodes('node[flag = 1]').id()
                && node.id() != cy.nodes('node[flag = 0]').id()) {
                    cy.nodes('node[id = "' + node.id() + '"]').style('background-color', 'white');
                }
            });
            cy.edges().forEach(function(edge) {
                edge.style('line-color', 'white');
            });
        });
       
        $("#print_paths").click(function() {
            data.paths.forEach(function(p) {
                print_path(p.path);
            });
        });
        
        function        print_path(path) {
            var color = getRandomColor();
            var j;
            for (j = 0; j < path.length; j++)  {
                if (path[j] != cy.nodes('node[flag = 1]').id()
                && path[j] != cy.nodes('node[flag = 0]').id()) {
                room = path[j];
                    cy.nodes('node[id = "' + path[j] + '"]').style('background-color', color);
                }
                tunnel = cy.edges().filter(function(edge) {
                    var e1 = (edge.source().id() == path[j] && edge.target().id() == path[j + 1]);
                    var e2 = (edge.source().id() == path[j + 1] && edge.target().id() == path[j]);
                    return e1 || e2;
                });
                tunnel.style('line-color', color);
            }
        }
        
        function        getRandomColor() {
            var letters = '0123456789ABCDEF';
            var color = '#';
            
            for (var i = 0; i < 6; i++) {
                color += letters[Math.floor(Math.random() * 16)];
            }
            return color;
        }

        $("#next").click(function() {
            if (k < data.rounds) {
                var points = moves[k];
                origins.forEach(function(origin) {
                    if (origin.dest != cy.nodes('node[flag = 0]').id()
                    && origin.dest != cy.nodes('node[flag = 1]').id()) {
                        cy.elements('node[id = "' + origin.dest + '"]')
                            .style('background-color', 'white');
                 }
                });
                tunnels.forEach(function(tunnel) {
                    tunnel.style('line-color', 'white');
                });
                points.forEach(function(point) {
                    if (point.dest != cy.nodes('node[flag = 1]').id()) {
                        cy.nodes('node[id = "' + point.dest + '"]')
                            .style('background-color', 'rgb(252, 181, 74)');

                    } else {
                        ants_out++;
                    } 
  
                    from = getParentNode(point.dest, point.ant_id);
                    tunnel = cy.edges().filter(function(elem) {
                        var e1 = (from.id() == elem.source().id() && elem.target().id() == point.dest);
                        var e2 = (elem.source().id() == point.dest && from.id() == elem.target().id());
                        return e1 || e2;
                    }); 
                    tunnel.style('line-color', 'rgb(252, 181, 74)');
                    tunnels.push(tunnel);
                    data.nodes.forEach(function(node) {
                        if (node.data.id == point.dest)
                            node.data.ant_id = point.ant_id;
                    });  
                });
                origins = points;
                k += 1;
                $("#rounds").text(k);
                $("#out").text(ants_out);
            } else {
                cy.edges().forEach(function(edge) {
                    edge.style('line-color', 'white');
                });
            }
        });

        function        getParentNode(dest, ant_id) {
            var src;
            if (dest == cy.nodes('node[flag = 1]').id()) {
                src = getParentMatchingAntId(ant_id);
            } else {
                data.paths.forEach(function(p) {
                    var n = 0;
                    while (n < p.path.length) {
                        if (p.path[n] == dest && n == 1) {
                            src = cy.nodes('node[flag = 0]');
                        } else if (p.path[n] == dest) {
                            src = cy.nodes('node[id = "' + p.path[n - 1] + '"]');
                        }
                        n += 1;
                    }
                });
            }
            return src;
        }

        function        getParentMatchingAntId(ant_id) {
            var matching_node;
            data.nodes.forEach(function(node) {
                if (node.data.ant_id == ant_id) {
                    matching_node = cy.nodes('node[id = "' + node.data.id + '"]');;
                }
            });
            return (matching_node);
        }

        $("#play").click(function() {
            pause = false;
            play_button();
 
          });
        
        function        play_button() {
            var timeOut;
            if (data.moves.length > 50)
                timeOut = 10;
            else if (data.moves.length > 20)
                timeOut = 200;
            else
                timeOut = 500;
            if (ants_out != data.ant_qty && pause == false) {
                setTimeout(function() {
                    $("#next").trigger("click");
                    play_button();
                }, timeOut);
            } else {
                cy.edges().forEach(function(edge) {
                    edge.style('line-color', 'white');
                });
            }
        }

        $("#pause").click(function() {
            pause = true;
        });
	});
});

function            copyObject(src) {
    return Object.assign({}, src);
}
