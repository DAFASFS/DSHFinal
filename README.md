# DSHFinal
### Evaluación 3 Asignatura desarrollo de software para hardware

## Objetivos:
  Como principal objetivo de este proyecto se realizo un sistema IoT mediante Esp-32 utilizado como Hotspot, el cual pueda conectarse con multiples Esp-32, estos realizan sus tareas correspondientes, las cuales son:

      1. Medir o Sensar temperatura ambiente y enviarla a una base de datos
      2. Indicador de luces led temperatura actual usando una base de datos
      
  Como Segundo objetivo se busca tener una interfaz Web utilizando Flask python, la cual nos permitira ver de forma grafica la temperatura actual del sistema.

## Diagrama de flujo
[Diagrama de flujo.drawio](https://github.com/user-attachments/files/29725057/Diagrama.de.flujo.drawio)

      

<mxfile host="app.diagrams.net">
  <diagram name="Página-1" id="QUKLlT000Gw6gwyS3GKb">
    <mxGraphModel dx="1030" dy="575" grid="1" gridSize="10" guides="1" tooltips="1" connect="1" arrows="1" fold="1" page="1" pageScale="1" pageWidth="827" pageHeight="1169" math="0" shadow="0">
      <root>
        <mxCell id="0" />
        <mxCell id="1" parent="0" />
        <mxCell id="vZNrdoE1pbVYWpoFujhw-3" parent="1" style="rounded=1;whiteSpace=wrap;html=1;" value="ESP #1&lt;div&gt;Hotspot&lt;/div&gt;" vertex="1">
          <mxGeometry height="60" width="120" x="354" y="110" as="geometry" />
        </mxCell>
        <mxCell id="vZNrdoE1pbVYWpoFujhw-10" parent="1" style="rounded=1;whiteSpace=wrap;html=1;" value="ESP #2&lt;div&gt;Temperatura&lt;/div&gt;" vertex="1">
          <mxGeometry height="60" width="120" x="279" y="230" as="geometry" />
        </mxCell>
        <mxCell id="vZNrdoE1pbVYWpoFujhw-11" parent="1" style="rounded=1;whiteSpace=wrap;html=1;" value="ESP #3&lt;div&gt;LEDS&lt;/div&gt;" vertex="1">
          <mxGeometry height="60" width="120" x="430" y="230" as="geometry" />
        </mxCell>
        <mxCell id="vZNrdoE1pbVYWpoFujhw-23" parent="1" style="rounded=1;whiteSpace=wrap;html=1;" value="Python Fl&lt;span style=&quot;background-color: transparent; color: light-dark(rgb(0, 0, 0), rgb(255, 255, 255));&quot;&gt;ask&lt;/span&gt;&lt;div&gt;&lt;div&gt;MariaDB&lt;/div&gt;&lt;/div&gt;" vertex="1">
          <mxGeometry height="60" width="120" x="210" y="110" as="geometry" />
        </mxCell>
        <mxCell id="vZNrdoE1pbVYWpoFujhw-24" edge="1" parent="1" style="endArrow=classic;html=1;rounded=0;entryX=0;entryY=0.5;entryDx=0;entryDy=0;" target="vZNrdoE1pbVYWpoFujhw-3" value="">
          <mxGeometry height="50" relative="1" width="50" as="geometry">
            <mxPoint x="330" y="140" as="sourcePoint" />
            <mxPoint x="380" y="90" as="targetPoint" />
          </mxGeometry>
        </mxCell>
        <mxCell id="vZNrdoE1pbVYWpoFujhw-30" edge="1" parent="1" style="endArrow=classic;html=1;rounded=0;" value="">
          <mxGeometry height="50" relative="1" width="50" as="geometry">
            <mxPoint x="413" y="200" as="sourcePoint" />
            <mxPoint x="413" y="170" as="targetPoint" />
          </mxGeometry>
        </mxCell>
        <mxCell id="vZNrdoE1pbVYWpoFujhw-35" edge="1" parent="1" style="endArrow=none;html=1;rounded=0;" value="">
          <mxGeometry height="50" relative="1" width="50" as="geometry">
            <mxPoint x="490" y="200" as="sourcePoint" />
            <mxPoint x="340" y="200" as="targetPoint" />
          </mxGeometry>
        </mxCell>
        <mxCell id="vZNrdoE1pbVYWpoFujhw-36" edge="1" parent="1" style="endArrow=none;html=1;rounded=0;" value="">
          <mxGeometry height="50" relative="1" width="50" as="geometry">
            <mxPoint x="340" y="230" as="sourcePoint" />
            <mxPoint x="340" y="200" as="targetPoint" />
          </mxGeometry>
        </mxCell>
        <mxCell id="vZNrdoE1pbVYWpoFujhw-37" edge="1" parent="1" style="endArrow=none;html=1;rounded=0;entryX=0.5;entryY=0;entryDx=0;entryDy=0;" target="vZNrdoE1pbVYWpoFujhw-11" value="">
          <mxGeometry height="50" relative="1" width="50" as="geometry">
            <mxPoint x="490" y="200" as="sourcePoint" />
            <mxPoint x="540" y="150" as="targetPoint" />
          </mxGeometry>
        </mxCell>
      </root>
    </mxGraphModel>
  </diagram>
</mxfile>
